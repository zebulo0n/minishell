/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:51:38 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/06 23:51:50 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	je_sais_meme_pas(t_minishell *ms, t_redir *current_redir,
		int last_heredoc_fd)
{
	while (current_redir)
	{
		if (current_redir->type == INPUT)
		{
			if (handle_input_file(ms, current_redir) == -1)
				return (-1);
		}
		else if (current_redir->type == HEREDOC)
		{
			if (last_heredoc_fd != -1)
				close(last_heredoc_fd);
			last_heredoc_fd = current_redir->fd;
		}
		current_redir = current_redir->next;
	}
	return (0);
}

int	handle_input_redirection(t_minishell *ms, t_cmd *current_cmd)
{
	t_redir	*current_redir;
	int		last_heredoc_fd;

	current_redir = current_cmd->redir;
	last_heredoc_fd = -1;
	if (je_sais_meme_pas(ms, current_redir, last_heredoc_fd) == -1)
		return (-1);
	if (last_heredoc_fd != -1)
	{
		if (dup2(last_heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
		close(last_heredoc_fd);
	}
	return (0);
}

int	handle_input_file(t_minishell *ms, t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		error_handler(ms, string_array(ms, redir->file, NULL, NULL), errno,
			false);
		return (-1);
	}
	safe_dup2(ms, fd, STDIN_FILENO);
	safe_close(ms, &fd);
	return (0);
}

/* MY FIRST HANDLE HEREDOC (THAT DOEST'T WORK WITH SIGNALS)
int	handle_heredoc(t_minishell *ms, t_redir *redir, bool is_last_heredoc)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		printf("herdoc errno : %d\n", errno);
		error_handler(ms, string_array(ms, "pipe", NULL, NULL), errno, false);
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		if (redir->quoted_heredoc == false && *line)
			handle_expansions(ms, &line, &ms->env_list);
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	if (is_last_heredoc)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			//printf("dup2 errno : %d\n", errno);
			error_handler(ms, string_array(ms, "dup2", NULL, NULL), errno,
				false);
			close(pipe_fd[0]);
			return (-1);
		}
	}
	close(pipe_fd[0]);
	return (0);
}*/
