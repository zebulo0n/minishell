/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:11:00 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/06 23:38:15 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	cmptr;

	if (!str)
		return (0);
	cmptr = 0;
	while (str[cmptr])
		cmptr++;
	return (cmptr);
}

/*
#include <string.h>
#include <stdio.h>

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	printf("%lu\n", strlen(""));
	printf("%lu\n", ft_strlen(""));
}
*/
