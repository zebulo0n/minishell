/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:13:11 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:13:12 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_shell(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

int	signals_handler(void)
{
	struct sigaction	sa_c;
	struct sigaction	sa_s;

	sigemptyset(&sa_c.sa_mask);
	sigemptyset(&sa_s.sa_mask);
	sa_c.sa_flags = SA_RESTART;
	sa_s.sa_flags = SA_RESTART;
	sa_c.sa_handler = handler_shell;
	sa_s.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa_c, NULL) == -1 || sigaction(SIGQUIT, &sa_s,
			NULL) == -1)
		write(2, "signal failed\n", 15);
	return (0);
}
