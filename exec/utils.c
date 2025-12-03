/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:53:49 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/07 00:40:10 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_elements_in_cmd_lst(t_cmd *cmd_lst)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd_lst;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	count_elements_in_env_lst(t_env *env_lst)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_lst;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**convert_env_list_to_envp(t_minishell *ms, t_env *env_list)
{
	int		size;
	char	**envp;
	int		i;

	i = 0;
	size = count_elements_in_env_lst(env_list);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	while (env_list)
	{
		if (env_list->value)
			envp[i] = ft_strjoin_three(ms, env_list->key, "=", env_list->value);
		else
			envp[i] = safe_strjoin(ms, env_list->key, "=");
		if (!envp[i])
		{
			free_array_pointer(&envp);
			error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno,
				true);
		}
		env_list = env_list->next;
		i++;
	}
	return (envp[i] = NULL, envp);
}

char	*get_env_value(t_minishell *ms, char *key)
{
	t_env	*env;

	env = ms->env_list;
	while (env)
	{
		if (strict_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
