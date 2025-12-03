/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:34:47 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/05 16:12:35 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>

int main (int ac, char *av[])
{
        (void)ac;
        printf("%s\n", strrchr(av[1], av[2][0]));
        printf("%s", ft_strrchr(av[1], av[2][0]));
}
*/
