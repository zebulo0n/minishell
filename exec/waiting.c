/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:29:24 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/07 00:36:17 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_and_get_status(t_minishell *ms, pid_t pid)
{
	int	wstatus;
	int	status;
	int	sig;

	wstatus = 0;
	status = 1;
	if (waitpid(pid, &wstatus, 0) == -1)
		error_handler(ms, string_array(ms, "waitpid", NULL, NULL), errno,
			false);
	if (WIFSIGNALED(wstatus))
	{
		sig = WTERMSIG(wstatus);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
	if (WIFEXITED(wstatus))
		status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		status = 128 + WTERMSIG(wstatus);
	else
		status = 1;
	ms->last_exit_status = (uint8_t)status;
	return (status);
}

int	wait_for_children(t_minishell *ms, int count, int *child_pids)
{
	int	i;
	int	wstatus;
	int	exit_code;

	exit_code = 0;
	i = 0;
	while (i < count)
	{
		if (waitpid(child_pids[i], &wstatus, 0) == -1)
			error_handler(ms, string_array(ms, "waitpid", NULL, NULL), errno,
				false);
		else if (i == count - 1)
		{
			if (WIFEXITED(wstatus))
				exit_code = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				exit_code = 128 + WTERMSIG(wstatus);
			else
				exit_code = 1;
		}
		i++;
	}
	ms->last_exit_status = (uint8_t)exit_code;
	return (exit_code);
}

int	wait_for_heredoc_child(t_minishell *ms, pid_t pid, int pipe_read_fd,
		t_redir *redir)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		error_handler(ms, string_array(ms, "waitpid", NULL, NULL), errno,
			false);
		close(pipe_read_fd);
		return (-1);
	}
	return (handle_heredoc_child_status(ms, status, pipe_read_fd, redir));
}

int	handle_heredoc_child_status(t_minishell *ms, int status,
		int pipe_read_fd, t_redir *redir)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ms->last_exit_status = 130;
			close(pipe_read_fd);
			redir->fd = -1;
			return (-1);
		}
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipe_read_fd);
		redir->fd = -1;
		return (-1);
	}
	return (0);
}
