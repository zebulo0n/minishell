/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:51:05 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/28 14:03:33 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	else
		return (2048);
}
/*
#include <stdio.h>
#include <ctype.h>

int main(int ac, char *av[])
{
	(void)ac;
	printf("%d\n", isdigit(av[1][0]));
	printf("%d\n", ft_isdigit(av[1][0]));
}
*/
