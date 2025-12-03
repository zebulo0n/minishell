/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:48:14 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/28 14:10:41 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	else
		return (16384);
}
/*
#include <stdio.h>
#include <ctype.h>

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	printf("%d\n", isprint(31));
	printf("%d\n", ft_isprint(31));
}
*/
