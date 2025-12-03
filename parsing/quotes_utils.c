/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:13:31 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:26:10 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_delim(char c)
{
	return (c == '\0' || is_space(c) || is_token(c));
}

char	*append_segment(t_minishell *ms, char **dst, char **seg)
{
	char	*result;

	if (!*seg && !*dst)
		return (NULL);
	if (!*seg)
	{
		result = safe_strdup(*dst, ms);
	}
	else if (!*dst)
	{
		result = safe_strdup(*seg, ms);
	}
	else
		result = safe_strjoin(ms, *dst, *seg);
	if (!result)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	free(*dst);
	free(*seg);
	*dst = NULL;
	*seg = NULL;
	return (result);
}

char	*str_append_char(t_minishell *ms, char *s, char c)
{
	char	buf[2];
	char	*str;
	char	*result;

	buf[0] = c;
	buf[1] = '\0';
	str = safe_strdup(buf, ms);
	result = append_segment(ms, &s, &str);
	return (result);
}

void	handle_unquoted_char(t_minishell *ms, char *line, int *i, char **buf)
{
	if (line[*i] == '\\' && line[*i + 1])
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

void	build_unquoted_content(t_minishell *ms, char *line, int *i, char **buf)
{
	while (line[*i] && !is_delim(line[*i]) && line[*i] != '"'
		&& line[*i] != '\'')
		handle_unquoted_char(ms, line, i, buf);
}
