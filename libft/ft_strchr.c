/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:27:04 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/06 23:37:51 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s || !c)
		return (NULL);
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

/*
#include <string.h>
#include <stdio.h>

int main (int ac, char *av[])
{
	(void)ac;
	(void)av;
	//printf("%s\n", strchr(av[1], av[2][0]));
	//printf("%s", ft_strchr(av[1], av[2][0]));
	printf("%s\n", strchr("teste", '\0'));
        printf("%s\n", ft_strchr("teste", '\0'));
}
*/
