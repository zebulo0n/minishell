/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:24:16 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/29 19:51:53 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <string.h>
#include <stdio.h>

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	//printf("%s\n", (char*)memset(av[1], atoi(av[2]), atoi(av[3])));
	//printf("%s", (char*)ft_memset(av[1], atoi(av[2]), atoi(av[3])));
	int c = 90;
	size_t n = 10;
	//printf("%s\n", (char*)memset(NULL, c, n));
        printf("%s", (char*)ft_memset(NULL, c, n));
}
*/
