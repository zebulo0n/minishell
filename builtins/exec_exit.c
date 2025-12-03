/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:25:20 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:25:21 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ll_atoi(const char *nptr)
{
	long long	nb;
	int			sign;

	nb = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb *= 10;
		nb = nb + (*nptr - 48);
		nptr++;
	}
	return (nb * sign);
}
static bool	is_number(const char *str);

int	exec_exit(t_minishell *ms, t_cmd *cmd)
{
	long long	code;

	write(STDOUT_FILENO, "exit\n", 5);
	if (!cmd->args[1])
		clean_exit(ms, ms->last_exit_status);
	code = ll_atoi(cmd->args[1]);
	if (is_number(cmd->args[1]) == false || code > LONG_MAX || code < LONG_MIN)
	{
		ms->last_exit_status = 2;
		error_handler(ms, string_array(ms, "exit", cmd->args[1],
				"numeric argument required"), -2, true);
	}
	if (cmd->args[2])
	{
		ms->last_exit_status = 1;
		error_handler(ms, string_array(ms, "exit", "too many arguments", NULL),
			0, false);
		return (1);
	}
	code %= 256;
	clean_exit(ms, (uint8_t)code);
	return (0);
}

static bool	is_number(const char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/*
CAS : pas d'arguments
CAS : un argument non numérique
CAS : plusieurs arguments
CAS : un argument numérique
*/
