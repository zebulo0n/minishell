/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:35:21 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/06 10:24:33 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb *= 10;
		nb = nb + (*nptr - 48);
		nptr++;
	}
	return (nb * sign);
}
/*
#include <stdlib.h>
#include <stdio.h>

int main (int ac, char *av[])
{
	(void)ac;
	printf("%d\n", atoi(av[1]));
	printf("%d\n", ft_atoi(av[1]));
}
*/
