/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:14:15 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/06 23:39:02 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	int		total_size;
// 	int		i;
// 	int		j;

// 	total_size = ft_strlen(s1) + ft_strlen(s2);
// 	str = (char *)malloc(sizeof(char) * total_size + 1);
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i])
// 		str[j++] = s1[i++];
// 	i = 0;
// 	while (s2[i])
// 		str[j++] = s2[i++];
// 	str[j] = '\0';
// 	return (str);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	return (res);
}

/*
#include <stdio.h>

int	main(int ac, char *av[])
{
	(void)ac;
	printf("%s", ft_strjoin(av[1], av[2]));
}
*/
