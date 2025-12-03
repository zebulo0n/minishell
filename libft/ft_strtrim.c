/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:22:24 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/02 18:44:09 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	int		i;
	int		start;
	int		end;

	start = 0;
	while (is_set(s1[start], set) && s1[start])
		start++;
	end = ft_strlen(s1);
	while (is_set(s1[end - 1], set) && end > start)
		end--;
	strim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!strim)
		return (NULL);
	i = 0;
	while (start < end)
		strim[i++] = s1[start++];
	strim[i] = '\0';
	return (strim);
}
/*
static int
    ft_char_in_set(char c, char const *set)
{
    size_t    i;

    i = 0;
    while (set[i])
    {
        if (set[i] == c)
            return (1);
        i++;
    }
    return (0);
}

char
    *ft_sstrtrim(char const *s1, char const *set)
{
    char    *str;
    size_t    i;
    size_t    start;
    size_t    end;

    start = 0;
    while (s1[start] && ft_char_in_set(s1[start], set))
        start++;
    end = ft_strlen(s1);
    while (end > start && ft_char_in_set(s1[end - 1], set))
        end--;
    str = (char*)malloc(sizeof(*s1) * (end - start + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (start < end)
        str[i++] = s1[start++];
    str[i] = 0;
    return (str);
}

#include <stdio.h>

int main(int ac, char *av[])
{
	(void)ac;
	printf("%s ||||\n", ft_sstrtrim(av[1], av[2]));
	printf("%s ||||", ft_strtrim(av[1], av[2]));
}
*/
