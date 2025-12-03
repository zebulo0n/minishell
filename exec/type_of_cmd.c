/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:49:58 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/06 23:49:59 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_single_cmd(t_cmd *cmds)
{
	if (cmds && cmds->next == NULL)
		return (true);
	return (false);
}

bool	is_first_cmd(t_cmd *cmd)
{
	if (cmd && cmd->index == 0)
		return (true);
	return (false);
}

bool	is_last_cmd(t_cmd *cmd)
{
	if (cmd && cmd->next == NULL)
		return (true);
	return (false);
}

bool	is_middle_cmd(t_cmd *cmd)
{
	if (cmd && cmd->index != 0 && cmd->next != NULL)
		return (true);
	return (false);
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}
