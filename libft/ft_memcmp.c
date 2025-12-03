/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:51:51 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/02 17:31:56 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ucp1;
	const unsigned char	*ucp2;

	ucp1 = (const unsigned char *)s1;
	ucp2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ucp1[i] != ucp2[i])
			return (ucp1[i] - ucp2[i]);
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
	printf("%d\n", ft_memcmp(av[1], av[2], atoi(av[3])));
	printf("%d\n", memcmp(av[1], av[2], atoi(av[3])));
}
*/
