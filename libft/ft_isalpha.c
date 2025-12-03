/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:36:09 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/28 14:01:44 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z'))
		return (0);
	else
		return (1024);
}
/*
#include <ctype.h>
#include <stdio.h>

int main(int ac, char *av[])
{
	(void)ac;
	printf("%d\n", isalpha(av[1][0]));
	printf("%d\n", ft_isalpha(av[1][0]));
}
*/
