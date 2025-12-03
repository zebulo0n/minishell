/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:25:35 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:32:06 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(t_minishell *ms, t_env **env, char *path)
{
	char	*old_pwd;
	t_env	*tmp;

	tmp = *env;
	while (tmp && strict_strcmp(tmp->key, "PWD"))
		tmp = tmp->next;
	if (!tmp)
		return ;
	old_pwd = tmp->value;
	tmp->value = safe_strdup(path, ms);
	tmp = *env;
	while (tmp && strict_strcmp(tmp->key, "OLDPWD"))
		tmp = tmp->next;
	if (tmp)
	{
		free(tmp->value);
		tmp->value = old_pwd;
	}
	else
		add_node(env, new_node(ms, safe_split(ms, ft_strjoin_three(ms, "OLDPWD",
						"=", old_pwd), '=')));
}

// Handle the case with no arguments: use HOME
static char	*get_home_path(t_minishell *ms)
{
	char	*home;

	home = get_env_value(ms, "HOME");
	if (!home)
	{
		error_handler(ms, string_array(ms, "cd", "HOME not set", NULL), 0,
			false);
		return (NULL);
	}
	return (home);
}

// Handle relative path: build cwd + "/" + arg
static char	*get_relative_path(t_minishell *ms, char *arg, bool *to_free)
{
	char	*cwd;
	char	*full_path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		error_handler(ms, string_array(ms, "cd", "getcwd", NULL), errno, false);
		return (NULL);
	}
	full_path = ft_strjoin_three(ms, cwd, "/", arg);
	free(cwd);
	if (!full_path)
	{
		error_handler(ms, string_array(ms, "cd", "malloc", NULL), errno, true);
		return (NULL);
	}
	*to_free = true;
	return (full_path);
}

// Perform the actual directory change
static int	change_directory(t_minishell *ms, t_env **env, char *path,
		bool to_free)
{
	if (chdir(path) == -1)
	{
		error_handler(ms, string_array(ms, "cd", path, NULL), errno, false);
		if (to_free)
			free(path);
		return (1);
	}
	update_pwd(ms, env, path);
	if (to_free)
		free(path);
	return (0);
}

// Main cd command logic
int	exec_cd(t_minishell *ms, t_env **env, char **args)
{
	char	*path;
	bool	to_free;

	path = NULL;
	to_free = false;
	if (!args || !args[1])
		path = get_home_path(ms);
	else if (args[2])
	{
		error_handler(ms, string_array(ms, "cd", "too many arguments", NULL), 0,
			false);
		return (1);
	}
	else if (args[1][0] == '/')
		path = args[1];
	else
		path = get_relative_path(ms, args[1], &to_free);
	if (!path)
		return (1);
	return (change_directory(ms, env, path, to_free));
}

// error mess wrong
// int	exec_cd(t_minishell *ms, t_env **env, char **args)
// {
// 	char	*path;
// 	char	*cwd;
// 	bool	to_free;

// 	path = NULL;
// 	to_free = false;
// 	if (!args || !args[1])
// 	{
// 		path = get_env_value(ms, "HOME");
// 		if (path == NULL)
// 		{
// 			error_handler(ms, string_array(ms, "cd", "HOME not set", NULL), 0,
// 				false);
// 			return (1);
// 		}
// 	}
// 	else if (args[2])
// 	{
// 		error_handler(ms, string_array(ms, "cd", "too many arguments", NULL), 0,
// 			false);
// 		return (1);
// 	}
// 	else if (args[1][0] == '/')
// 		path = args[1];
// 	else
// 	{
// 		cwd = getcwd(NULL, 0);
// 		if (!cwd)
// 		{
// 			error_handler(ms, string_array(ms, "cd", "getcwd", NULL), errno,
// 				false);
// 			return (1);
// 		}
// 		path = ft_strjoin_three(ms, cwd, "/", args[1]);
// 		to_free = true;
// 		free(cwd);
// 	}
// 	if (chdir(path) == -1)
// 	{
// 		if (to_free)
// 			free(path);
// 		error_handler(ms, string_array(ms, "cd", args[1], NULL), errno, false);
// 		return (1);
// 	}
// 	update_pwd(ms, env, path);
// 	if (to_free)
// 		free(path);
// 	return (0);
// }
