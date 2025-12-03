/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:59:11 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/05 12:03:57 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	cmptr;

	cmptr = 0;
	while (lst != NULL)
	{
		cmptr++;
		lst = lst->next;
	}
	return (cmptr);
}
/*
#include <stdio.h>

int main()
{
        t_list *first = ft_lstnew((void *)10);
        first->next = ft_lstnew((void *)20);
        first->next->next = ft_lstnew((void *)30);
//	ft_lstadd_front(&first, ft_lstnew((void *)50));
	t_list *tmp = first;
        while (tmp)
        {
                printf("%d\t", (int)(intptr_t)tmp->content);
                tmp = tmp->next;
        }
	printf("\n%d\n", ft_lstsize(first));
}
*/
