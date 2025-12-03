/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:27:22 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/02 19:35:06 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*strm;
	int		i;

	strm = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!strm)
		return (NULL);
	i = 0;
	while (s[i])
	{
		strm[i] = (*f)(i, s[i]);
		i++;
	}
	strm[i] = '\0';
	return (strm);
}
