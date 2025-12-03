/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:50:04 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/30 19:11:52 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(long int nb)
{
	int	cmptr;

	cmptr = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= 10;
		cmptr++;
	}
	return (cmptr);
}

char	*fill_nb(char *array, long int nb, int size, int sign)
{
	int	i;

	array[size] = '\0';
	if (nb == 0)
	{
		array[0] = '0';
		return (array);
	}
	i = size - 1;
	while (nb > 0)
	{
		array[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (sign == 1)
		array[0] = '-';
	return (array);
}

char	*ft_itoa(int n)
{
	char	*array;
	int		sign;
	int		size;
	long	nb;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		sign++;
		nb = -nb;
	}
	size = ft_numlen(nb) + sign;
	array = malloc(sizeof(char) * (size + 1));
	if (!array)
		return (NULL);
	return (fill_nb(array, nb, size, sign));
}
/*
#include <string.h>
#include <stdio.h>

int main (int ac, char *av[])
{
	(void)ac;
	printf("%s", ft_itoa(atoi(av[1])));
}
*/
