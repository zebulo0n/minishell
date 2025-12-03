/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:47:32 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/06 23:36:20 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while ((i + j) < len && little[j] && big[i + j]
			&& (little[j] == big[i + j]))
			j++;
		if (j == ft_strlen(little))
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

// char
//     *ft_sstrnstr(const char *haystack, const char *needle, size_t len)
// {
//     size_t    i;
//     size_t    j;

//     if (!haystack || !needle)
//         return (NULL);
//     if (!needle || !needle[0])
//         return ((char*)haystack);
//     i = 0;
//     while (haystack[i] && i < len)
//     {
//         j = 0;
//         while (haystack[i + j] && needle[j] &&
//                 i + j < len && haystack[i + j] == needle[j])
//             j++;
//         if (!needle[j])
//             return ((char*)(haystack + i));
//         i++;
//     }
//     return (NULL);
// }

// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main (int ac, char *av[])
// {
// 	(void)ac;
// 	//printf("%s\n", ft_sstrnstr(av[1], av[2], atoi(av[3])));
// 	printf("%s", ft_strnstr(av[1], av[2], atoi(av[3])));
// }
