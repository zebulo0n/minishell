/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:09:52 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:21:51 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_charset(char c, char *charset)
{
	int	i;

	if (c == '\0')
		return (1);
	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_wording(char *str, char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_charset(str[i], sep) == 0 && is_charset(str[i + 1], sep) == 1)
			count++;
		i++;
	}
	return (count);
}

char	*word_filling(t_minishell *ms, char *str, int start, int end)
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
	return (word);
}

char	**tf_split(t_minishell *ms, char *str, char *charset, int *cmptr)
{
	char	**array;
	int		start;
	int		i;
	int		j;

	*cmptr = count_wording(str, charset);
	array = malloc(sizeof(char *) * (count_wording(str, charset) + 1));
	if (!array)
		error_handler(ms, string_array(ms, "tf_split", NULL, NULL), errno,
			true);
	i = 0;
	j = 0;
	while (j < count_wording(str, charset))
	{
		start = i;
		while (str[i] && is_charset(str[i], charset) == 1)
			i++;
		while (str[i] && is_charset(str[i], charset) == 0)
			i++;
		array[j++] = word_filling(ms, str, start, i);
		if (!array[j - 1])
			return (free_split(array, j - 1), NULL);
	}
	array[j] = NULL;
	return (array);
}
