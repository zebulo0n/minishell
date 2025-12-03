/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:48:56 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:50:04 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_token(t_minishell *ms, char *str, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	i = 0;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	add_token(&ms->tokens_list, new_token(ms, WORD, word, false));
}

void	handle_token(t_minishell *ms, char *line, t_token **tokens, int *i)
{
	if (line[*i] == '|')
	{
		add_token(tokens, new_token(ms, PIPE, NULL, false));
		(*i)++;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(tokens, new_token(ms, APPEND, NULL, false));
		*i += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(tokens, new_token(ms, HEREDOC, NULL, false));
		*i += 2;
	}
	else if (line[*i] == '>')
	{
		add_token(tokens, new_token(ms, OUTPUT, NULL, false));
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		add_token(tokens, new_token(ms, INPUT, NULL, false));
		(*i)++;
	}
}

char	*handle_quotes(t_minishell *ms, char *line, t_token **tokens, int *i)
{
	char	*assembled;

	assembled = NULL;
	if (line[*i] == '\'')
	{
		if (!parse_single_quoted(ms, line, i, &assembled))
		{
			free(assembled);
			return_error("minishell: syntax error: unclosed single quote\n",
				assembled, tokens);
			return (NULL);
		}
	}
	else if (line[*i] == '"')
	{
		if (!parse_double_quoted(ms, line, i, &assembled))
		{
			free(assembled);
			return_error("minishell: syntax error: unclosed double quote\n",
				assembled, tokens);
			return (NULL);
		}
	}
	return (assembled);
}

bool	unclosed_quotes(char *assembled)
{
	free(assembled);
	return (false);
}

bool	handle_word(t_minishell *ms, char *line, t_token **tokens, int *i)
{
	char *(assembled) = NULL;
	int (start_pos) = *i;
	char *(segment) = NULL;
	bool (quoted) = true;
	while (line[*i] && !is_delim(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			segment = handle_quotes(ms, line, tokens, i);
			if (!segment)
				return (unclosed_quotes(assembled));
			assembled = append_segment(ms, &assembled, &segment);
		}
		else
		{
			if (!parse_unquoted(ms, line, i, &assembled))
				return (return_error(NULL, assembled, tokens));
			quoted = false;
		}
	}
	if (!assembled)
		assembled = safe_substr(ms, line, start_pos, *i - start_pos);
	add_token(tokens, new_token(ms, WORD, assembled, quoted));
	return (true);
}
