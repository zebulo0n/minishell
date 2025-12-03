/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:55:51 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/02 19:25:00 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	sub_len;
	char	*sub;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	sub_len = s_len - start;
	if (sub_len > len)
		sub_len = len;
	sub = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < sub_len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
/*
#include <stdio.h>

int main(int ac, char *av[])
{
	(void)ac;
	printf("%s", ft_substr(av[1], atoi(av[2]), atoi(av[3])));
}
*/
