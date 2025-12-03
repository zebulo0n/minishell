/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:33:25 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/05 11:58:42 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
#include <stdio.h>

int main()
{
	t_list *first = ft_lstnew((void *)10);
	first->next = ft_lstnew((void *)20);
	first->next->next = ft_lstnew((void *)30);
	t_list *tmp = first;
	while (tmp)
	{
		printf("%d\n", (int)(intptr_t)tmp->content);
		tmp = tmp->next;
	}
	return 0;
}
*/
