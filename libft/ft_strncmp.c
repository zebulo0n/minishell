/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:41:42 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/02 17:32:20 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_diff(unsigned char s1, unsigned char s2)
{
	return (s1 != s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	uc1;
	unsigned char	uc2;

	i = 0;
	while (i < n)
	{
		uc1 = (unsigned char)s1[i];
		uc2 = (unsigned char)s2[i];
		if (is_diff(uc1, uc2) || uc1 == '\0' || uc2 == '\0')
			return (uc1 - uc2);
		i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int ac, char *av[])
{
	(void)ac;
	(void)av;
	printf("%d\n", strncmp("\x12\xff\x65\x12\xbd\xde\xad", "\x12\x02", 6));
	printf("%d", ft_strncmp("\x12\xff\x65\x12\xbd\xde\xad", "\x12\x02", 6));
}
*/
