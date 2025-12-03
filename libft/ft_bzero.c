/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:00:44 by zoeschne          #+#    #+#             */
/*   Updated: 2025/04/28 15:16:27 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
#include <strings.h>
#include <stdio.h>

int main()
{
	char str[50] = "GeeksForGeeks is for programming geeks.";
    printf("\nBefore memset(): %s\n", str);

    // Fill 8 characters starting from str[13] with '.'
    ft_bzero(str + 13, 8*sizeof(char));

    printf("After memset():  %s", str);
   char  str2[50] = "GeeksForGeeks is for programming geeks.";
    printf("\nBefore memset(): %s\n", str2);

    // Fill 8 characters starting from str[13] with '.'
    bzero(str2 + 13, 8*sizeof(char));

    printf("After memset():  %s", str2);
    return 0;
}
*/
