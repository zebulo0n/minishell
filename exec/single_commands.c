/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:54:47 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/07 00:29:47 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_single_cmd(t_minishell *ms, t_cmd *current)
{
	int	status;

	if (!current || (!current->cmd && (!current->args || !current->args[0])))
		return (1);
	safe_close(ms, &ms->saved_stdin);
	safe_close(ms, &ms->saved_stdout);
	ms->saved_stdin = dup(STDIN_FILENO);
	ms->saved_stdout = dup(STDOUT_FILENO);
	if (ms->saved_stdin == -1 || ms->saved_stdout == -1)
	{
		error_handler(ms, string_array(ms, "dup", NULL, NULL), errno, false);
		safe_close(ms, &ms->saved_stdin);
		safe_close(ms, &ms->saved_stdout);
		return (1);
	}
	if (is_builtin(current->cmd) && !does_builtin_need_forking(current->cmd))
		status = exec_builtin_in_parent(ms, current);
	else
		status = fork_and_exec_single(ms, current);
	restore_fds(ms);
	return (status);
}

int	fork_and_exec_single(t_minishell *ms, t_cmd *current)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		error_handler(ms, string_array(ms, "fork", NULL, NULL), errno, true);
		restore_fds(ms);
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_cmd_in_child(ms, current);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	status = wait_and_get_status(ms, pid);
	signals_handler();
	return (status);
}

int	exec_builtin_in_parent(t_minishell *ms, t_cmd *current)
{
	int	status;

	if (handle_input_redirection(ms, current) == -1)
	{
		restore_fds(ms);
		return (1);
	}
	if (handle_output_redirection(ms, current) == -1)
	{
		restore_fds(ms);
		return (1);
	}
	status = exec_builtin_cmd(ms, current);
	restore_fds(ms);
	return (status);
}

void	exec_cmd_in_child(t_minishell *ms, t_cmd *current)
{
	int	status;

	errno = 0;
	if (handle_input_redirection(ms, current) == -1)
		error_handler(ms, NULL, 0, true);
	if (handle_output_redirection(ms, current) == -1)
		error_handler(ms, NULL, 0, true);
	if (is_builtin(current->cmd))
	{
		status = exec_builtin_cmd(ms, current);
		cleanup_shell(ms, true);
		exit(status);
	}
	if (current->cmd_path)
	{
		free(current->cmd_path);
		current->cmd_path = NULL;
	}
	get_cmd_path(ms, current);
	status = exec_normal_cmd(ms, current);
	exit(status);
}

bool	does_builtin_need_forking(char *cmd)
{
	if (!cmd)
		return (false);
	if (strict_strcmp(cmd, "cd") == 0)
		return (false);
	if (strict_strcmp(cmd, "export") == 0)
		return (false);
	if (strict_strcmp(cmd, "unset") == 0)
		return (false);
	if (strict_strcmp(cmd, "exit") == 0)
		return (false);
	return (true);
}
