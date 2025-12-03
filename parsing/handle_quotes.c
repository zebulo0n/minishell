/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:13:51 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:25:31 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parse_single_quoted(t_minishell *ms, char *line, int *i, char **acc)
{
	int		start;
	char	*buf;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (!line[*i])
		return (false);
	buf = safe_substr(ms, line, start, *i - start);
	*acc = append_segment(ms, acc, &buf);
	(*i)++;
	return (true);
}

static void	handle_double_quoted_char(t_minishell *ms, char *line, int *i,
		char **buf)
{
	if (line[*i] == '\\' && line[*i + 1] && (line[*i + 1] == '"'
			|| line[*i + 1] == '\\'))
	{
		*buf = str_append_char(ms, *buf, line[*i + 1]);
		if (!*buf)
			error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno,
				true);
		*i += 2;
	}
	else
	{
		*buf = str_append_char(ms, *buf, line[*i]);
		if (!*buf)
			error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno,
				true);
		(*i)++;
	}
}

static bool	build_double_quoted_content(t_minishell *ms, char *line, int *i,
		char **buf)
{
	(*i)++;
	while (line[*i] && line[*i] != '"')
		handle_double_quoted_char(ms, line, i, buf);
	if (!line[*i])
	{
		free(*buf);
		return (false);
	}
	return (true);
}

bool	parse_double_quoted(t_minishell *ms, char *line, int *i, char **acc)
{
	char	*buf;

	buf = NULL;
	if (!build_double_quoted_content(ms, line, i, &buf))
		return (false);
	if (buf == NULL)
		buf = safe_strdup("", ms);
	*acc = append_segment(ms, acc, &buf);
	if (!*acc)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	(*i)++;
	if (ft_strchr(*acc, '$'))
		handle_expansions(ms, acc, &ms->env_list);
	return (true);
}

bool	parse_unquoted(t_minishell *ms, char *line, int *i, char **acc)
{
	char	*buf;

	buf = NULL;
	build_unquoted_content(ms, line, i, &buf);
	*acc = append_segment(ms, acc, &buf);
	if (!*acc)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	if (ft_strchr(*acc, '$'))
		handle_expansions(ms, acc, &ms->env_list);
	return (true);
}
