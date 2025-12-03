/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:52:08 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:54:02 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_var(t_minishell *ms, t_env **env, char *key, char *value)
{
	char	*tmp;
	char	**vars;

	tmp = ft_strjoin_three(ms, key, "=", value);
	if (!tmp)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	vars = safe_split(ms, tmp, '=');
	free(tmp);
	if (!vars)
		error_handler(ms, string_array(ms, "split", NULL, NULL), errno, true);
	add_node(env, new_node(ms, vars));
	free(vars);
}

void	mini_env(t_minishell *ms, t_env **env)
{
	char	*path;
	char	*joined;

	path = NULL;
	path = getcwd(NULL, 4096);
	if (!path)
		error_handler(ms, string_array(ms, "getcwd", NULL, NULL), errno, true);
	create_var(ms, env, "PWD", path);
	create_var(ms, env, "SHLVL", "1");
	joined = ft_strjoin_three(ms, path, "/", "./minishell");
	if (!joined)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	create_var(ms, env, "_", joined);
	free(joined);
	free(path);
}
