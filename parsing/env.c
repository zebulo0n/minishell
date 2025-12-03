/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:24:08 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:53:41 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_node(t_minishell *ms, char **vars)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	env->key = safe_strdup(vars[0], ms);
	env->value = safe_strdup(vars[1], ms);
	env->exported = true;
	env->ms = NULL;
	env->next = NULL;
	return (env);
}

void	add_node(t_env **list, t_env *env)
{
	t_env	*tmp;

	if (!(*list))
		*list = env;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = env;
	}
}

char	**env_split(char *s, char c)
{
	char	**array;
	int		start;
	int		i;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (2 + 1));
	if (!array)
		return (NULL);
	i = 0;
	start = 0;
	while (s && s[i] && s[i] != c)
		i++;
	array[0] = fill_word(s, start, i);
	if (!array[0])
		return (free_split(array, 0), NULL);
	start = ++i;
	while (s && s[i])
		i++;
	array[1] = fill_word(s, start, i);
	if (!array[1])
		return (free_split(array, 1), NULL);
	array[2] = NULL;
	return (array);
}

t_env	*init_env(t_minishell *ms, char **envp)
{
	int		i;
	char	**vars;
	t_env	*envs;

	vars = NULL;
	i = 0;
	envs = NULL;
	if (envp[0] == NULL)
		mini_env(ms, &envs);
	else
	{
		while (envp[i])
		{
			vars = env_split(envp[i], '=');
			if (!vars)
				error_handler(ms, string_array(ms, "split", envp[i], NULL),
					errno, true);
			add_node(&envs, new_node(ms, vars));
			free_array_pointer(&vars);
			i++;
		}
	}
	return (envs);
}
