/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:25:24 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:25:25 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// technically errno==127
int	exec_env(t_minishell *ms, t_env *env, char **args)
{
	t_env	*tmp;

	if (args[1])
	{
		error_handler(ms, string_array(ms, "env",
				"No options or arguments supported", NULL), 0, false);
		return (1);
	}
	tmp = env;
	while (tmp)
	{
		if (tmp && tmp->exported && tmp->value && tmp->value[0] != '\0')
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
