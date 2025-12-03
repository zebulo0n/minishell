/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:21:38 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/05 16:09:01 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lnode;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lnode = ft_lstlast(*lst);
	lnode->next = new;
}
/*
int main()
{
        t_list *first = ft_lstnew((void *)10);
        first->next = ft_lstnew((void *)20);
        first->next->next = ft_lstnew((void *)30);
	t_list *tmp = first;
	ft_lstadd_back(&first, ft_lstnew((void *)50));
        while (tmp)
        {
                printf("%d\n", (int)(intptr_t)tmp->content);
                tmp = tmp->next;
        }
}
*/
