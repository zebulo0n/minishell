/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:40:20 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/07 00:39:18 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prepare_heredocs(t_minishell *ms)
{
	t_cmd	*cmd;
	int		status;

	set_signal_handlers_parent_heredoc();
	cmd = ms->cmd_list;
	while (cmd)
	{
		status = handle_cmd_heredocs(ms, cmd);
		if (status == -1)
		{
			restore_signal_handlers_parent();
			return (-1);
		}
		cmd = cmd->next;
	}
	restore_signal_handlers_parent();
	return (0);
}

int	handle_cmd_heredocs(t_minishell *ms, t_cmd *cmd)
{
	t_redir	*redir;
	int		status;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			status = launch_heredoc_in_child(ms, redir);
			if (status == -1)
			{
				if (redir->fd >= 0)
				{
					close(redir->fd);
					redir->fd = -1;
				}
				close_heredoc_fds(ms);
				return (-1);
			}
		}
		redir = redir->next;
	}
	return (0);
}

void	process_heredoc_line(t_minishell *ms, t_redir *redir, char *line,
		int pipe_fd)
{
	if (!redir->quoted_heredoc)
		handle_expansions(ms, &line, &ms->env_list);
	if (write(pipe_fd, line, ft_strlen(line)) == -1 || write(pipe_fd, "\n",
			1) == -1)
	{
		error_handler(ms, string_array(ms, "write", NULL, NULL), errno, true);
	}
}

void	heredoc_child_process(t_minishell *ms, t_redir *redir, int *pipe_fd)
{
	char	*line;

	setup_heredoc_child_signals();
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		if (strict_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(ms, redir, line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

int	launch_heredoc_in_child(t_minishell *ms, t_redir *redir)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (create_heredoc_pipe(ms, redir, pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		error_handler(ms, string_array(ms, "fork", NULL, NULL), errno, false);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
		heredoc_child_process(ms, redir, pipe_fd);
	close(pipe_fd[1]);
	if (wait_for_heredoc_child(ms, pid, pipe_fd[0], redir) == -1)
		return (-1);
	redir->fd = pipe_fd[0];
	return (0);
}
