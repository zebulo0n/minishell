/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:07:46 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/29 20:12:07 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
	(void)ac;
	printf ("%s\n", (char*)ft_memchr(av[1], atoi(av[2]), atoi(av[3])));
	printf ("%s", (char*)memchr(av[1], atoi(av[2]), atoi(av[3])));
}
*/
