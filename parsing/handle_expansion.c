/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:15:18 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:15:49 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_segment(t_minishell *ms, char *token, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (is_key(&tmp, token))
		return (safe_strdup(tmp->value, ms));
	if (strict_strcmp(token, "$?") == 0)
		return (itoa_exit_code(ms));
	if (strict_strcmp(token, "$$") == 0)
		return (safe_itoa(ms, getpid()));
	if (token[0] == '$')
		return (NULL);
	return (safe_strdup(token, ms));
}

char	*gogo_expansion(t_minishell *ms, char *str, t_env **env)
{
	char	**tab;
	char	**res;
	int		i;

	i = 0;
	tab = sep_split(ms, str, "$/", &i);
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	i = 0;
	while (tab && tab[i])
	{
		res[i] = expand_segment(ms, tab[i], env);
		if (!res[i])
			res[i] = safe_strdup("", ms);
		i++;
	}
	res[i] = NULL;
	str = tab_to_str(ms, res);
	free_array_pointer(&res);
	free_array_pointer(&tab);
	return (str);
}

void	close_quotes(char **str)
{
	int	last_cell;

	if ((*str)[0] == '\'')
	{
		last_cell = ft_strlen(*str);
		(*str)[last_cell] = '\'';
	}
}

void	handle_expansions(t_minishell *ms, char **value, t_env **env)
{
	char	**tab;
	char	**res;
	char	*has_dollar;
	int		i;

	tab = tf_split(ms, *value, " \t\n'", &i);
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		error_handler(ms, string_array(ms, "malloc", NULL, NULL), errno, true);
	i = 0;
	while (tab && tab[i])
	{
		has_dollar = ft_strchr(tab[i], '$');
		if (has_dollar != NULL && *(has_dollar + 1) != '\0')
			res[i] = gogo_expansion(ms, tab[i], env);
		else
			res[i] = safe_strdup(tab[i], ms);
		i++;
	}
	res[i] = NULL;
	free_array_pointer(&tab);
	free(*value);
	*value = tab_to_str(ms, res);
	free_array_pointer(&res);
}
