/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:13:38 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:35:32 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmd(t_minishell *ms, t_cmd **cmd, t_token **token)
{
	t_token	*tmp;
	int		cmptr;

	(*cmd)->cmd = NULL;
	(*cmd)->redir = NULL;
	(*cmd)->next = NULL;
	(*cmd)->cmd_path = NULL;
	(*cmd)->ms = NULL;
	tmp = *token;
	cmptr = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redir(tmp->type) && tmp->next)
			tmp = tmp->next;
		else
			cmptr++;
		tmp = tmp->next;
	}
	(*cmd)->args = safe_calloc(ms, (size_t)(cmptr + 1), sizeof(char *));
	if (!(*cmd)->args)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
}

int	fill_redir(t_minishell *ms, t_cmd **cmd, t_token **token)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	redir->type = (*token)->type;
	redir->next = NULL;
	redir->quoted_heredoc = false;
	redir->ms = NULL;
	redir->fd = -1;
	*token = (*token)->next;
	if (!*token || (*token)->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
		free(redir);
		ms->last_exit_status = 2;
		return (0);
	}
	redir->file = (*token)->value;
	(*token)->value = NULL;
	append_redir(cmd, redir);
	if (redir->type == HEREDOC && (*token)->quoted == true)
		redir->quoted_heredoc = true;
	return (1);
}

int	fill_cmd(t_minishell *ms, t_cmd **cmd, t_token **token, int *i)
{
	if ((*token)->type == CMD)
	{
		(*cmd)->cmd = (*token)->value;
		if ((*cmd)->args[0])
			shift_args((*cmd)->args);
		(*cmd)->args[0] = safe_strdup((*cmd)->cmd, ms);
		(*token)->value = NULL;
		(*i)++;
	}
	else if ((*token)->type == WORD)
	{
		(*cmd)->args[(*i)++] = (*token)->value;
		(*token)->value = NULL;
	}
	else if (is_redir((*token)->type))
	{
		if (!fill_redir(ms, cmd, token))
			return (0);
	}
	return (1);
}

int	parse_cmd(t_minishell *ms, t_token **token, t_cmd **cmd_list, int index)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	init_cmd(ms, &cmd, token);
	cmd->index = index;
	while (*token && (*token)->type != PIPE)
	{
		if (!fill_cmd(ms, &cmd, token, &i))
		{
			free_cmd_list(&cmd);
			free_cmd_list(cmd_list);
			return (0);
		}
		*token = (*token)->next;
	}
	cmd->args[i] = NULL;
	if (cmd->cmd == NULL)
		no_cmd(&cmd, ms);
	append_cmd(&cmd, cmd_list);
	return (1);
}

int	parsing(t_minishell *ms, t_token *token, t_cmd **cmd_list)
{
	int	index;

	index = 0;
	while (token)
	{
		if (!parse_cmd(ms, &token, cmd_list, index))
			return (0);
		index++;
		if (token)
			token = token->next;
	}
	return (1);
}
