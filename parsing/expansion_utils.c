/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:24:01 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:24:02 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_char(char **tab)
{
	int	cmptr;
	int	i;
	int	j;

	i = 0;
	cmptr = 0;
	while (tab && tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			cmptr++;
			j++;
		}
		i++;
	}
	return (cmptr);
}

char	*tab_to_str(t_minishell *ms, char **tab)
{
	char	*str;
	int		size;
	int		i;
	char	*p;
	int		len;

	size = count_char(tab);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	p = str;
	i = 0;
	while (tab && tab[i])
	{
		len = ft_strlen(tab[i]);
		if (len > 0)
		{
			ft_memcpy(p, tab[i], len);
			p += len;
		}
		i++;
	}
	*p = '\0';
	return (str);
}

bool	is_key(t_env **tmp, char *str)
{
	while ((*tmp))
	{
		if (strict_strcmp((*tmp)->key, (str + 1)) == 0)
			return (true);
		(*tmp) = (*tmp)->next;
	}
	return (false);
}

int	count_word(char *str)
{
	int	i;
	int	cmptr;

	i = 0;
	cmptr = 0;
	if (str[0] != '$')
		cmptr++;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$')
		{
			cmptr++;
			i++;
		}
		else if (str[i] == '$' && str[i + 1] == '$')
		{
			cmptr++;
			i += 2;
		}
		else
			i++;
	}
	return (cmptr);
}
