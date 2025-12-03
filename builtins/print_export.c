/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:25:04 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:50:44 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_size(t_env *lst)
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

char	**struct_to_tab(t_env **env)
{
	char	**tab;
	t_env	*tmp;

	int (i) = 0;
	int (cmptr) = 0;
	tmp = *env;
	tab = malloc(sizeof(char *) * (env_size(tmp) + 1));
	if (!tab)
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (tmp->exported && strict_strcmp(tmp->key, "_") != 0)
		{
			if (tmp->value)
				tab[i] = ft_strjoin_three(tmp->ms, tmp->key, "=", tmp->value);
			else
				tab[i] = safe_strdup(tmp->key, (*env)->ms);
			cmptr++;
			i++;
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	tab_size(char **tab)
{
	int	cmptr;

	cmptr = 0;
	while (tab && tab[cmptr])
		cmptr++;
	return (cmptr);
}

void	bubble_sort(char **tab)
{
	int		ext;
	int		itn;
	int		size;
	char	*tmp;

	size = tab_size(tab);
	ext = 0;
	while (ext < (size - 1))
	{
		itn = ext + 1;
		while (itn < size)
		{
			if (ft_strcmp(tab[ext], tab[itn]) > 0)
			{
				tmp = tab[ext];
				tab[ext] = tab[itn];
				tab[itn] = tmp;
			}
			itn++;
		}
		ext++;
	}
}

void	print_export(t_env **env)
{
	char	**tab;
	int		i;

	tab = struct_to_tab(env);
	bubble_sort(tab);
	i = 0;
	while (tab && tab[i])
	{
		printf("export %s\n", tab[i]);
		i++;
	}
	free_array_pointer(&tab);
}
