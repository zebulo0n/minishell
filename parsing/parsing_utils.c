/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:13:44 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:36:39 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_cmd(t_cmd **cmd, t_cmd **cmds)
{
	t_cmd	*tmp;

	if (*cmds == NULL)
		*cmds = *cmd;
	else
	{
		tmp = *cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *cmd;
	}
}

bool	is_redir(t_type type)
{
	if (type == INPUT || type == OUTPUT || type == HEREDOC || type == APPEND)
		return (true);
	else
		return (false);
}

void	shift_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	while (i > 0)
	{
		args[i] = args[i - 1];
		i--;
	}
	args[0] = NULL;
}

void	append_redir(t_cmd **cmd, t_redir *redir)
{
	t_redir	*tmp;

	if (!(*cmd)->redir)
		(*cmd)->redir = redir;
	else
	{
		tmp = (*cmd)->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

void	no_cmd(t_cmd **cmd, t_minishell *ms)
{
	if (ft_strchr((*cmd)->args[0], '=') == NULL)
		(*cmd)->cmd = safe_strdup((*cmd)->args[0], ms);
}
