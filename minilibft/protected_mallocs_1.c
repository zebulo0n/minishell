/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_mallocs_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:24:22 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:24:23 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*safe_calloc(t_minishell *ms, size_t nmemb, size_t size)
{
	void	*mem;

	if ((nmemb * size) >= 2147483647)
		return (0);
	mem = (void *)malloc(size * nmemb);
	if (!mem)
		error_handler(ms, string_array(ms, "calloc", NULL, NULL), errno, true);
	ft_memset(mem, 0, (nmemb * size));
	return (mem);
}

char	*safe_word(t_minishell *ms, const char *str, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		error_handler(ms, string_array(ms, "calloc", NULL, NULL), errno, true);
	i = 0;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**safe_split(t_minishell *ms, char const *s, char c)
{
	char	**array;
	int		start;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!array)
		error_handler(ms, string_array(ms, "split", NULL, NULL), errno, true);
	i = 0;
	j = 0;
	while (s[i] && j < word_count(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		array[j++] = safe_word(ms, s, start, i);
		if (!array[j - 1])
			return (free_split(array, j - 1), NULL);
	}
	array[j] = NULL;
	return (array);
}

char	*safe_strdup(const char *src, t_minishell *ms)
{
	char	*cpy;
	size_t	x;

	if (src == NULL)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!cpy)
		error_handler(ms, string_array(ms, "strdup", NULL, NULL), errno, true);
	x = 0;
	while (x < ft_strlen(src))
	{
		cpy[x] = src[x];
		x++;
	}
	cpy[x] = '\0';
	return (cpy);
}

char	*safe_itoa(t_minishell *ms, int n)
{
	char	*array;
	int		sign;
	int		size;
	long	nb;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		sign++;
		nb = -nb;
	}
	size = ft_numlen(nb) + sign;
	array = malloc(sizeof(char) * (size + 1));
	if (!array)
		error_handler(ms, string_array(ms, "itoa", NULL, NULL), errno, true);
	return (fill_nb(array, nb, size, sign));
}
