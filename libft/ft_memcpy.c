/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:08:18 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/30 11:04:22 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	//printf("%s\n", (char*)memcpy(NULL, NULL, 12));
	printf("%s\n", (char*)ft_memcpy(NULL, "nwfjeo", 12));
	char csrc[] = "bonjour comment ca va";
	memcpy(csrc+5, csrc, strlen(csrc)+1);
	printf("%s\n", csrc);
	char csrcc[100] = "bonjour comment ca va";
        ft_memcpy(csrcc+5, csrcc, strlen(csrcc)+1);
        printf("%s", csrc);
	return 0;
}
*/
