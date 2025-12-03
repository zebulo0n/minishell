/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:25:17 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:53:14 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *s)
{
	char	*key;
	int		i;
	int		cmptr;

	cmptr = 0;
	while (s[cmptr] && s[cmptr] != '=' && s[cmptr] != '+')
		cmptr++;
	key = malloc(sizeof(char) * (cmptr + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (i < cmptr)
	{
		key[i] = s[i];
		i++;
	}
	key[i] = '\0';
	cmptr++;
	return (key);
}

void	add_var(t_env **env, char *key, char *value, bool exported)
{
	t_env	*node;

	node = find_node(env, key);
	if (node)
	{
		if (value)
		{
			free(node->value);
			node->value = safe_strdup(value, (*env)->ms);
		}
		if (exported)
			node->exported = exported;
		return ;
	}
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->key = safe_strdup(key, (*env)->ms);
	if (value)
		node->value = safe_strdup(value, (*env)->ms);
	else
		node->value = NULL;
	node->exported = exported;
	node->next = NULL;
	add_node(env, node);
}

void	append_var(t_env *env, char *key, char *value, bool exported)
{
	t_env	*node;
	char	*joined;

	node = find_node(&env, key);
	if (node)
	{
		if (value)
		{
			joined = safe_strjoin(env->ms, node->value, value);
			free(node->value);
			node->value = joined;
		}
		if (exported)
			node->exported = exported;
		return ;
	}
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->key = safe_strdup(key, env->ms);
	node->value = safe_strdup(value, env->ms);
	node->exported = exported;
	node->next = NULL;
	add_node(&env, node);
}

// Handles a single export argument (validation + env update)
static int	handle_single_export(t_minishell *ms, t_env **env, char *arg)
{
	char	*key;
	char	*value;

	if (!var_valid(arg))
	{
		error_handler(ms, string_array(ms, "export", arg,
				"not a valid identifier"), 0, false);
		return (1);
	}
	key = get_key(arg);
	value = ft_strchr(arg, '=');
	if (value == NULL)
		add_var(env, key, NULL, true);
	else if (*(value - 1) == '+')
		append_var(*env, key, (value + 1), true);
	else
		add_var(env, key, (value + 1), true);
	free(key);
	return (0);
}

// Main export builtin
int	exec_export(t_minishell *ms, t_env **env, char **args)
{
	int	i;
	int	status;

	if (!args[1])
	{
		print_export(env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		status = handle_single_export(ms, env, args[i]);
		if (status != 0)
			return (status);
		i++;
	}
	return (0);
}
