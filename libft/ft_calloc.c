/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:15:21 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/05 21:34:10 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "../minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if ((nmemb * size) >= 2147483647)
		return (0);
	mem = (void *)malloc(size * nmemb);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, (nmemb * size));
	return (mem);
}
/*
#include <stdio.h>

int main()
{
	int *ptr = (int *)ft_calloc(sizeof(int), 0);

    // Do some operations.....
    for (int i = 0; i < 15; i++)
        printf("%d ", ptr[i]);

    // Free the memory after completing
    // operations
    free(ptr);
}
*/
