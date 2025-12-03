/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:27:38 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/07 00:40:04 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Handle absolute or relative paths containing '/'
static bool	handle_direct_path(t_minishell *ms, t_cmd *cmd)
{
	if (access(cmd->cmd, F_OK) != 0)
	{
		error_handler(ms, string_array(ms, cmd->cmd,
				"No such file or directory", NULL), -127, false);
		return (true);
	}
	if (access(cmd->cmd, X_OK) != 0)
	{
		error_handler(ms, string_array(ms, cmd->cmd, "Permission denied", NULL),
			-126, false);
		return (true);
	}
	cmd->cmd_path = safe_strdup(cmd->cmd, ms);
	return (true);
}

// Search PATH directories for an executable
static void	search_path_for_cmd(t_minishell *ms, t_cmd *cmd, char **dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin_three(ms, dirs[i], "/", cmd->cmd);
		if (!full_path)
			error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno,
				true);
		if (access(full_path, X_OK) == 0)
		{
			cmd->cmd_path = full_path;
			return ;
		}
		free(full_path);
		i++;
	}
}

// Handle PATH-based command lookup
static void	resolve_cmd_via_path(t_minishell *ms, t_cmd *cmd)
{
	char	*path_str;
	char	**path_dirs;

	path_str = get_env_value(ms, "PATH");
	if (!path_str)
		return ;
	path_dirs = safe_split(ms, path_str, ':');
	if (!path_dirs)
	{
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
		return ;
	}
	search_path_for_cmd(ms, cmd, path_dirs);
	free_array_pointer(&path_dirs);
}

// Main entry point
void	get_cmd_path(t_minishell *ms, t_cmd *cmd)
{
	if (!cmd || !cmd->cmd || cmd->cmd[0] == '\0')
		return ;
	if (cmd->cmd_path)
	{
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	if (ft_strchr(cmd->cmd, '/') != NULL)
	{
		handle_direct_path(ms, cmd);
		return ;
	}
	resolve_cmd_via_path(ms, cmd);
}

void	reset_cmd_paths(t_minishell *ms)
{
	t_cmd	*current;

	current = ms->cmd_list;
	while (current)
	{
		if (current->cmd_path)
		{
			free(current->cmd_path);
			current->cmd_path = NULL;
		}
		current = current->next;
	}
}
