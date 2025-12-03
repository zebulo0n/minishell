/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:14:22 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/28 14:08:14 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c < 0 || c > 127)
		return (0);
	else
		return (1);
}
/*
#include <ctype.h>
#include <stdio.h>

int main ()
{
	int i = -1;
	printf("%d\n", isascii(i));
	printf("%d\n", ft_isascii(i));
}
*/
