/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:13:21 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:49:24 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_empty(t_token **tokens)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*to_free;

	if (!tokens || !*tokens)
		return ;
	tmp = *tokens;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type == WORD && is_empty(tmp->value))
		{
			to_free = tmp;
			if (prev == NULL)
				*tokens = tmp->next;
			else
				prev->next = tmp->next;
			tmp = tmp->next;
			free(to_free->value);
			free(to_free);
			continue ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	handle_cmd(t_token **tokens)
{
	t_token	*tmp;
	bool	one_cmd;

	one_cmd = true;
	tmp = *tokens;
	while (tmp)
	{
		if (is_redir(tmp->type) && tmp->next)
			tmp = tmp->next;
		else if (tmp->type == WORD && one_cmd == true
			&& (is_empty(tmp->value) == 0 || (is_empty(tmp->value) == 1
					&& tmp->quoted == true)))
		{
			tmp->type = CMD;
			one_cmd = false;
		}
		else if (tmp->type == PIPE)
			one_cmd = true;
		tmp = tmp->next;
	}
}

t_token	*tokenizer(t_minishell *ms, char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_token(line[i]))
			handle_token(ms, line, &tokens, &i);
		else if (!handle_word(ms, line, &tokens, &i))
			return (NULL);
	}
	handle_cmd(&tokens);
	if (tokens && tokens->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		free_token_list(&tokens);
		ms->last_exit_status = 2;
		return (NULL);
	}
	return (tokens);
}
