/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:55:56 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/06 23:37:04 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_count(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] != sep && str[i])
		{
			count++;
			while (str[i] && str[i] != sep)
				i++;
		}
	}
	return (count);
}

void	free_split(char **array, int count)
{
	while (count--)
		free(array[count]);
	free(array);
}

char	*fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		start;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < word_count(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		array[j++] = fill_word(s, start, i);
		if (!array[j - 1])
			return (free_split(array, j - 1), NULL);
	}
	array[j] = NULL;
	return (array);
}
/*
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str = "\0aa\0bbb";
    char delimiter = '\0';
    char **result = ft_split(str, delimiter);

    if (!result)
    {
        printf("ft_split returned NULL\n");
        return 1;
    }

    int i = 0;
    while (i < 7)
    {
        printf("result[%d]: %s\n", i, result[i]);
        i++;
    }

    return 0;
}
*/
