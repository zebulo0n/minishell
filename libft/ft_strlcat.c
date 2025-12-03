/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:42:57 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/30 11:55:52 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dlen;
	size_t	slen;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (dlen < (size - 1) && size)
	{
		i = 0;
		j = dlen;
		while (src[i] && (dlen + i) < (size - 1))
			dest[j++] = src[i++];
		dest[j] = '\0';
	}
	if (dlen >= size)
		dlen = size;
	return (dlen + slen);
}
/*
size_t
    ft_strllcat(char *dst, const char *src, size_t size)
{
    size_t    i;
    size_t    j;
    size_t    dest_length;
    size_t    src_length;

    src_length = ft_strlen(src);
    dest_length = ft_strlen(dst);
    j = dest_length;
    i = 0;
    if (dest_length < size - 1 && size > 0)
    {
        while (src[i] && dest_length + i < size - 1)
        {
            dst[j] = src[i];
            j++;
            i++;
        }
        dst[j] = 0;
    }
    if (dest_length >= size)
        dest_length = size;
    return (dest_length + src_length);
}

#include <stdio.h>
#include <string.h>

int    main(void)
{
    char    dest[] = "qwertyui";
    char    src[] = "iasdfghjkl";
    size_t    size = 0;

    size_t res = ft_strlcat(dest, src, size);
    printf("%s\n", dest);
    printf("%lu\n", res);
	
    char    dest1[] = "qwertyui";
    char    src1[] = "iasdfghjkl";
    size_t    size1 = 0;

    size_t res1 = ft_strllcat(dest1, src1, size1);
    printf("%s\n", dest1);
    printf("%lu", res1);
    return (0);
}
*/
