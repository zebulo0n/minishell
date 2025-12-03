/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:50:46 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/07 00:33:38 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_pipes(t_minishell *ms, int count)
{
	int	i;

	ms->pipe_count = count;
	ms->pipes = safe_calloc(ms, (size_t)(count - 1), sizeof(int *));
	if (!ms->pipes)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	i = 0;
	while (i < count - 1)
	{
		ms->pipes[i] = malloc(sizeof(int) * 2);
		if (!ms->pipes[i] || pipe(ms->pipes[i]) == -1)
		{
			if (ms->pipes[i])
				free(ms->pipes[i]);
			free_partially_allocated_pipes(&ms->pipes, i);
			error_handler(ms, string_array(ms, "pipe", NULL, NULL), errno,
				true);
		}
		i++;
	}
}

void	close_unused_pipes(t_minishell *ms, int **pipes, int count,
		t_cmd *current)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (!(is_first_cmd(current) && i == 0) && !(is_middle_cmd(current)
				&& (i == current->index - 1 || i == current->index))
			&& !(is_last_cmd(current) && i == current->index - 1))
		{
			safe_close(ms, &pipes[i][0]);
			safe_close(ms, &pipes[i][1]);
		}
		i++;
	}
}

void	close_all_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

int	create_heredoc_pipe(t_minishell *ms, t_redir *redir, int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		redir->fd = -1;
		error_handler(ms, string_array(ms, "pipe", NULL, NULL), errno, false);
		return (-1);
	}
	return (0);
}
