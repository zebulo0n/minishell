/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:25:10 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:25:11 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pwd(t_minishell *ms)
{
	char	path[4096];

	if (getcwd(path, 4096) == NULL)
	{
		error_handler(ms, string_array(ms, "pwd: getcwd failed", NULL, NULL),
			errno, false);
		return (1);
	}
	printf("%s\n", path);
	return (0);
}
