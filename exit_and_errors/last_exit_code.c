/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_exit_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:31:06 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/07 11:56:48 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*itoa_exit_code(t_minishell *ms)
{
	char	*str;

	str = safe_itoa(ms, (int)(ms->last_exit_status));
	if (!str)
		return (NULL);
	return (str);
}

bool	return_error(char *mess, char *assembled, t_token **token_lst)
{
	ft_putstr_fd(mess, 2);
	free_token_list(token_lst);
	free(assembled);
	return (false);
}
