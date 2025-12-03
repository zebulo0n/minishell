/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:36:43 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/02 17:05:21 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst;
	const unsigned char	*sr;

	if (!dest && !src)
		return (NULL);
	dst = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	if (sr < dst)
	{
		while (n--)
			dst[n] = sr[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dst[i] = sr[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	char dst1[0xF0];
	char dst2[0xF0];
	char *data = "thiÃ� Ã�\xde\xad\xbe\xeftriÃ±g will be ÃžvÃ©rlapÃ©d !\r\n";
	int size = 0xF0 - 0xF;

	memset(dst1, 'A', sizeof(dst1));
	memset(dst2, 'A', sizeof(dst2));
	memcpy(dst1, data, strlen(data));
	memcpy(dst2, data, strlen(data));
	memmove(dst1, dst1 + 3, size);
	ft_memmove(dst2, dst2 + 3, size);
	printf("%s\n\n\n", (char*)dst1);
	printf("%s\n", (char*)dst2);
	//printf("%s\n", (char*)ft_memmove(av[1], av[2], atoi(av[3])));
	//printf("%s\n", (char*)memmove(av[1], av[2], atoi(av[3])));
	char        des[] = "mais encore";
    const char    sr[] = "pourquoi pas";
    size_t        nb;

    nb = 5;
    ft_memmove(des, sr, nb);
    printf("%s\n", des);
    char        des1[] = "mais encore";
    const char    sr1[] = "pourquoi pas";
    size_t        nb1;

    nb1 = 5;
    memmove(des1, sr1, nb1);
    printf("%s", des1);
	return 0;
}
*/
