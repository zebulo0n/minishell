/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:53:24 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/06 23:53:27 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_output_redirection(t_minishell *ms, t_cmd *current_cmd)
{
	t_redir	*redir;

	redir = current_cmd->redir;
	while (redir)
	{
		if (redir->type == OUTPUT)
		{
			if (handle_output_file(ms, redir) == -1)
				return (-1);
		}
		else if (redir->type == APPEND)
		{
			if (handle_append_file(ms, redir) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

int	handle_output_file(t_minishell *ms, t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_handler(ms, string_array(ms, redir->file, NULL, NULL), errno,
			false);
		return (-1);
	}
	safe_dup2(ms, fd, STDOUT_FILENO);
	safe_close(ms, &fd);
	return (0);
}

int	handle_append_file(t_minishell *ms, t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("append errno : %d\n", errno);
		error_handler(ms, string_array(ms, redir->file, NULL, NULL), errno,
			false);
		return (-1);
	}
	safe_dup2(ms, fd, STDOUT_FILENO);
	safe_close(ms, &fd);
	return (0);
}
