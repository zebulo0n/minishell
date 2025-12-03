/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:32:21 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/05 13:01:55 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = (*lst);
		(*lst) = new;
	}
}
/*
#include <stdio.h>

int main()
{
        t_list *first = ft_lstnew((void *)10);
        first->next = ft_lstnew((void *)20);
        first->next->next = ft_lstnew((void *)30);
	ft_lstadd_front(&first, ft_lstnew((void *)50));
	t_list *tmp = first;
        while (tmp)
        {
                printf("%d\n", (int)(intptr_t)tmp->content);
                tmp = tmp->next;
        }
}
*/
