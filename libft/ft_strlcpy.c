/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:01:42 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/02 15:23:02 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (len)
	{
		while (i < (len - 1) && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
/*
size_t	ft_strllcpy (char *dst, const char *src, size_t size)
{
	size_t    i;

    i = 0;
    if (size > 0)
    {
        while (src[i] && i < (size - 1))
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = 0;
    }
    while (src[i])
        i++;
    return (i);
}

#include <stdio.h>
#include <string.h>

int    main(void)
{
	char    ds[0];
    const char sr[] = "";
    size_t    size;
	size_t res;

    size = 0;
    res = ft_strlcpy(ds, sr, size);
    printf("%s\n", ds);
	printf("%lu\n", res);
	char    ds1[0];
    const char sr1[] = "";
    size_t    size1;

    size1 = 0;
    size_t res1 = ft_strllcpy(ds1, sr1, size1);
    printf("%s\n", ds1);
	printf("%lu", res1);
    return (0);
}
*/
