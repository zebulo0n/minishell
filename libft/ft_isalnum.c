/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:58:00 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/28 15:17:49 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (8);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int main(int ac, char *av[])
{
	(void)ac;
	printf("%d\n", isalnum(av[1][0]));
	printf("%d\n", ft_isalnum(av[1][0]));
}
*/
