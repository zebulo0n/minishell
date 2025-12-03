/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:35:31 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/06 23:35:32 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd_list(t_cmd **cmd_lst)
{
	t_cmd	*tmp;

	if (!cmd_lst || !*cmd_lst)
		return ;
	while (*cmd_lst)
	{
		tmp = *cmd_lst;
		*cmd_lst = (*cmd_lst)->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			free_array_pointer(&tmp->args);
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->redir)
			free_redir_list(&tmp->redir);
		free(tmp);
	}
	*cmd_lst = NULL;
}
