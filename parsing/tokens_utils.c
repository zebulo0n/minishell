/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:13:27 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:13:28 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_empty(const char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_token	*new_token(t_minishell *ms, t_type type, char *value, bool quoted)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (!value)
		token->value = NULL;
	else
	{
		token->value = safe_strdup(value, ms);
		free(value);
	}
	token->quoted = quoted;
	token->ms = NULL;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **list, t_token *token)
{
	t_token	*tmp;

	if (!(*list))
		*list = token;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}
