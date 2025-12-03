/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:35:27 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/06 23:35:28 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_pipes(t_minishell *ms)
{
	int	i;

	i = 0;
	if (!ms || !ms->pipes)
		return ;
	while (i < ms->pipe_count - 1)
	{
		if (ms->pipes[i])
		{
			if (ms->pipes[i][0] >= 0)
			{
				safe_close(ms, &ms->pipes[i][0]);
				ms->pipes[i][0] = -1;
			}
			if (ms->pipes[i][1] >= 0)
			{
				safe_close(ms, &ms->pipes[i][1]);
				ms->pipes[i][1] = -1;
			}
		}
		i++;
	}
	free_pipes(&ms->pipes, ms->pipe_count);
	ms->pipes = NULL;
	ms->pipe_count = 0;
}

void	free_pipes(int ***pipes, int count)
{
	int	i;

	if (!pipes || !*pipes)
		return ;
	i = 0;
	while (i < count - 1)
	{
		free((*pipes)[i]);
		(*pipes)[i] = NULL;
		i++;
	}
	free(*pipes);
	*pipes = NULL;
}

void	free_partially_allocated_pipes(int ***pipes, int limit)
{
	int	j;

	if (!pipes || !*pipes)
		return ;
	j = 0;
	while (j < limit)
	{
		free((*pipes)[j]);
		(*pipes)[j] = NULL;
		j++;
	}
	free(*pipes);
	*pipes = NULL;
}
