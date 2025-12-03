/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:45:34 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/06 23:39:25 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*cpy;
	size_t	x;

	if (src == NULL)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!cpy)
		return (NULL);
	x = 0;
	while (x < ft_strlen(src))
	{
		cpy[x] = src[x];
		x++;
	}
	cpy[x] = '\0';
	return (cpy);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	printf("%s\n", strdup(""));
	printf("%s", ft_strdup(""));
}
*/
