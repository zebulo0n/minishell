/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:35:38 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/06 23:35:39 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redir_list(t_redir **redir)
{
	t_redir	*current;
	t_redir	*next;

	if (!redir || !*redir)
		return ;
	current = *redir;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
	*redir = NULL;
}
