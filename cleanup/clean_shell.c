/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:35:40 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/06 23:35:41 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_shell(t_minishell *ms, bool clean_env)
{
	if (!ms)
		return ;
	if (ms->cmd_list)
		close_heredoc_fds(ms);
	if (ms->pipes)
		cleanup_pipes(ms);
	if (ms->cmd_list)
		free_cmd_list(&ms->cmd_list);
	if (ms->tokens_list)
		free_token_list(&ms->tokens_list);
	if (ms->env_list && clean_env == true)
		free_env_list(&ms->env_list);
	if (ms->child_pids)
	{
		free(ms->child_pids);
		ms->child_pids = NULL;
	}
	ms->cmd_list = NULL;
	ms->tokens_list = NULL;
	safe_close(ms, &ms->saved_stdin);
	safe_close(ms, &ms->saved_stdout);
	if (clean_env == true)
		ms->env_list = NULL;
}
