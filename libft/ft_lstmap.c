/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:21:23 by zoeschne          #+#    #+#             */
/*   Updated: 2025/05/05 16:45:08 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlist;
	t_list	*nnode;
	void	*ncontent;

	if (!lst)
		return (NULL);
	nlist = NULL;
	while (lst)
	{
		ncontent = f(lst->content);
		nnode = ft_lstnew(ncontent);
		if (!nnode)
		{
			del(ncontent);
			ft_lstclear(&nlist, del);
			return (NULL);
		}
		ft_lstadd_back(&nlist, nnode);
		lst = lst->next;
	}
	return (nlist);
}
/*
void multi(void *x)
{
	int *result = malloc(sizeof(int));
	if (!result)
		return (NULL);
	*result = (*(int *)(x)) * 2;
	return (result);
}

void del(void *x)
{
	free(x);
}

int main()
{
        t_list *first = ft_lstnew((void *)10);
        first->next = ft_lstnew((void *)20);
        first->next->next = ft_lstnew((void *)30);
	ft_lstadd_front(&first, ft_lstnew((void *)50));
	t_list *tmp = first;
        while (tmp)
        {
                printf("%d\n", *(int *)tmp->content);
                tmp = tmp->next;
        }
	t_list *second = ft_lstmap(first, &multi, &del);
	tmp = second;
	while (second)
	{
		printf("%d\n", *(int *)second->content);
		second = second->next;
	}
}
*/
