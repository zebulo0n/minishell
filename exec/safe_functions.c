/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:53:49 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/07 00:38:52 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	safe_dup2(t_minishell *ms, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		error_handler(ms, string_array(ms, "dup2", NULL, NULL), errno, true);
	}
}

void	safe_close(t_minishell *ms, int *fd)
{
	if ((!fd) || (*fd < 0))
		return ;
	if (close(*fd) == -1)
	{
		error_handler(ms, string_array(ms, "close", NULL, NULL), errno, false);
	}
	*fd = -1;
}

void	restore_fds(t_minishell *ms)
{
	if (!ms)
		return ;
	if (ms->saved_stdin >= 0)
	{
		dup2(ms->saved_stdin, STDIN_FILENO);
		safe_close(ms, &ms->saved_stdin);
	}
	if (ms->saved_stdout >= 0)
	{
		dup2(ms->saved_stdout, STDOUT_FILENO);
		safe_close(ms, &ms->saved_stdout);
	}
}

void	close_heredoc_fds(t_minishell *ms)
{
	t_cmd	*cmd;
	t_redir	*current_redir;

	cmd = ms->cmd_list;
	while (cmd)
	{
		current_redir = cmd->redir;
		while (current_redir)
		{
			if (current_redir->type == HEREDOC && current_redir->fd != -1)
			{
				close(current_redir->fd);
				current_redir->fd = -1;
			}
			current_redir = current_redir->next;
		}
		cmd = cmd->next;
	}
}
