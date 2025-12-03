/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:26:42 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/07 00:40:24 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(t_minishell *ms, t_cmd *current_cmd)
{
	int	status;

	status = 0;
	if (handle_input_redirection(ms, current_cmd) == -1)
		error_handler(ms, NULL, 0, true);
	if (handle_output_redirection(ms, current_cmd) == -1)
		error_handler(ms, NULL, 0, true);
	if (is_builtin(current_cmd->cmd))
	{
		status = exec_builtin_cmd(ms, current_cmd);
		cleanup_shell(ms, true);
		exit(status);
	}
	if (current_cmd->cmd_path)
	{
		free(current_cmd->cmd_path);
		current_cmd->cmd_path = NULL;
	}
	else
	{
		get_cmd_path(ms, current_cmd);
		status = exec_normal_cmd(ms, current_cmd);
		exit(status);
	}
}

int	add_var_shell(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '=') && var_valid(cmd->args[i]))
		{
			key = get_key(cmd->args[i]);
			value = ft_strchr(cmd->args[i], '=');
			if (value == NULL)
				add_var(env, key, NULL, false);
			else if (*(value - 1) == '+')
				append_var(*env, key, (value + 1), false);
			else
				add_var(env, key, (value + 1), false);
			free(key);
		}
		i++;
	}
	return (0);
}

int	exec_builtin_cmd(t_minishell *ms, t_cmd *current_cmd)
{
	if (strict_strcmp(current_cmd->cmd, "echo") == 0)
		return (exec_echo(current_cmd->args));
	else if (strict_strcmp(current_cmd->cmd, "cd") == 0)
		return (exec_cd(ms, &ms->env_list, current_cmd->args));
	else if (strict_strcmp(current_cmd->cmd, "pwd") == 0)
		return (exec_pwd(ms));
	else if (strict_strcmp(current_cmd->cmd, "export") == 0)
		return (exec_export(ms, &ms->env_list, current_cmd->args));
	else if (strict_strcmp(current_cmd->cmd, "unset") == 0)
		return (exec_unset(&ms->env_list, current_cmd->args));
	else if (strict_strcmp(current_cmd->cmd, "env") == 0)
		return (exec_env(ms, ms->env_list, current_cmd->args));
	else if (strict_strcmp(current_cmd->cmd, "exit") == 0)
		return (exec_exit(ms, current_cmd));
	return (0);
}

void	handle_execve_errors(t_minishell *ms, t_cmd *cmd)
{
	if (errno == ENOENT || errno == 14)
	{
		error_handler(ms, string_array(ms, cmd->args[0], "command not found",
				NULL), -127, false);
	}
	else if (errno == EACCES)
	{
		error_handler(ms, string_array(ms, cmd->args[0], "Permission denied",
				NULL), -126, false);
	}
	else if (errno == EISDIR)
	{
		error_handler(ms, string_array(ms, cmd->args[0], "Is a directory",
				NULL), -126, false);
	}
	else
	{
		error_handler(ms, string_array(ms, cmd->args[0], "execve error", NULL),
			errno, false);
	}
}

int	exec_normal_cmd(t_minishell *ms, t_cmd *cmd)
{
	char	**envp;

	if (!cmd || !cmd->cmd)
		clean_exit(ms, 1);
	if (!cmd->cmd_path)
	{
		error_handler(ms, string_array(ms, cmd->args[0], "command not found",
				NULL), -127, false);
	}
	envp = convert_env_list_to_envp(ms, ms->env_list);
	if (!envp)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	execve(cmd->cmd_path, cmd->args, envp);
	free_array_pointer(&envp);
	handle_execve_errors(ms, cmd);
	cleanup_shell(ms, false);
	exit(ms->last_exit_status);
}
