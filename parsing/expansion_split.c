/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:02:35 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:16:23 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dollars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}

static int	count_words(char *str, char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = count_dollars(str);
	while (str[i])
	{
		if (!is_charset(str[i], sep) && is_charset(str[i + 1], sep))
			count++;
		i++;
	}
	return (count);
}

static char	*fill_words(t_minishell *ms, char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		error_handler(ms, string_array(ms, "fill_words", NULL, NULL), errno,
			true);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static char	*extract_segments(t_minishell *ms, char *s, int *i, char *sep)
{
	int	start;

	if (s[*i] && s[*i + 1] && s[*i] == '$' && s[*i + 1] == '$')
	{
		*i += 2;
		return (safe_strdup("$$", ms));
	}
	start = *i;
	while (s[*i] && is_charset(s[*i], sep))
		(*i)++;
	while (s[*i] && !is_charset(s[*i], sep))
		(*i)++;
	return (fill_words(ms, s, start, *i));
}

char	**sep_split(t_minishell *ms, char *s, char *sep, int *cmptr)
{
	char	**array;
	int		count;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	count = count_words(s, sep);
	*cmptr = count;
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		error_handler(ms, string_array(ms, "sep_split", NULL, NULL), errno,
			true);
	i = 0;
	j = 0;
	while (j < count)
	{
		array[j] = extract_segments(ms, s, &i, sep);
		if (!array[j])
			return (free_split(array, j), NULL);
		j++;
	}
	array[j] = NULL;
	return (array);
}
