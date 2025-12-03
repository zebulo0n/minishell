/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:25:08 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:51:59 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_key(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*curr;
	t_env	*to_free;

	prev = NULL;
	curr = *env;
	while (curr && strict_strcmp(curr->key, key) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr)
	{
		if (prev == NULL)
			*env = curr->next;
		else
			prev->next = curr->next;
		to_free = curr;
		free(to_free->key);
		free(to_free->value);
		free(to_free);
	}
	else
		return (0);
	return (1);
}

int	exec_unset(t_env **env, char **args)
{
	int	i;
	int	fail;

	if (!env || !*env || !args)
		return (1);
	i = 1;
	fail = 0;
	while (args[i])
	{
		if (!unset_key(env, args[i]))
			fail++;
		i++;
	}
	return (0);
}

//export utils
bool	var_valid(char *s)
{
	int	i;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (false);
	i = 1;
	while (s[i] && s[i] != '=' && !(s[i] == '+' && s[i + 1] == '='))
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

t_env	*find_node(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (strict_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
