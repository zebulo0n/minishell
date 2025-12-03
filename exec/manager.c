/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:50:26 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/07 00:30:35 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_manager(t_minishell *ms)
{
	int	status;

	if (!ms)
		return (1);
	if (ms->cmd_list)
		update_last_arg_var(ms, ms->cmd_list);
	if (ms->cmd_list && ft_strchr(ms->cmd_list->cmd, '=') != NULL
		&& var_valid(ms->cmd_list->cmd))
	{
		status = add_var_shell(ms->cmd_list, &ms->env_list);
		return (status);
	}
	else if (is_single_cmd(ms->cmd_list))
	{
		status = handle_single_cmd(ms, ms->cmd_list);
		return (status);
	}
	else
	{
		status = handle_multiple_commands(ms);
	}
	close_heredoc_fds(ms);
	return (status);
}

int	handle_multiple_commands(t_minishell *ms)
{
	int	count;
	int	status;
	int	i;

	count = count_elements_in_cmd_lst(ms->cmd_list);
	setup_pipes(ms, count);
	ms->child_pids = malloc(sizeof(int) * count);
	if (!ms->child_pids)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	reset_cmd_paths(ms);
	fork_and_execute(ms, count, ms->pipes, ms->child_pids);
	i = 0;
	while (i < count - 1)
	{
		safe_close(ms, &ms->pipes[i][0]);
		safe_close(ms, &ms->pipes[i][1]);
		i++;
	}
	status = wait_for_children(ms, count, ms->child_pids);
	signals_handler();
	cleanup_pipes(ms);
	free(ms->child_pids);
	ms->child_pids = NULL;
	return (status);
}

void	fork_and_execute(t_minishell *ms, int count, int **pipes,
		int *child_pids)
{
	pid_t	pid;
	t_cmd	*current;

	current = ms->cmd_list;
	if (current->index < 0 || current->index >= count)
		error_handler(ms, NULL, 0, true);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (current)
	{
		pid = fork();
		if (pid == 0)
			directing_child_processes(ms, current, pipes, count);
		else if (pid < 0)
		{
			error_handler(ms, string_array(ms, "fork", NULL, NULL), errno,
				true);
			close_all_pipes(ms->pipes, count);
			return ;
		}
		child_pids[current->index] = pid;
		current = current->next;
	}
}

void	directing_child_processes(t_minishell *ms, t_cmd *current, int **pipes,
		int count)
{
	if (is_first_cmd(current))
	{
		safe_dup2(ms, pipes[0][1], STDOUT_FILENO);
		safe_close(ms, &pipes[0][1]);
		safe_close(ms, &pipes[0][0]);
	}
	else if (is_middle_cmd(current))
	{
		safe_dup2(ms, pipes[current->index - 1][0], STDIN_FILENO);
		safe_close(ms, &pipes[current->index - 1][0]);
		safe_close(ms, &pipes[current->index - 1][1]);
		safe_dup2(ms, pipes[current->index][1], STDOUT_FILENO);
		safe_close(ms, &pipes[current->index][1]);
		safe_close(ms, &pipes[current->index][0]);
	}
	else if (is_last_cmd(current))
	{
		safe_dup2(ms, pipes[current->index - 1][0], STDIN_FILENO);
		safe_close(ms, &pipes[current->index - 1][0]);
		safe_close(ms, &pipes[current->index - 1][1]);
	}
	close_unused_pipes(ms, pipes, count, current);
	execute_command(ms, current);
	cleanup_shell(ms, true);
	exit(ms->last_exit_status);
}

void	update_last_arg_var(t_minishell *ms, t_cmd *cmd)
{
	char	*last_arg;
	int		i;

	last_arg = NULL;
	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd && cmd->args && cmd->args[i])
		i++;
	if (cmd->args && cmd->args[i] && i >= 1)
		last_arg = cmd->args[i - 1];
	if (last_arg)
		add_var(&ms->env_list, "_", last_arg, true);
}
