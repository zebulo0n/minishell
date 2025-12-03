/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:42 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 12:06:43 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;
	char		*line;

	(void)ac;
	(void)av;
	init_minishell_env(&ms, envp);
	while (1)
	{
		line = handle_input_line(&ms);
		process_line(&ms, line);
		free(line);
		cleanup_shell(&ms, false);
	}
	return (ms.last_exit_status);
}

void	init_minishell_env(t_minishell *ms, char **envp)
{
	init_minishell(ms);
	ms->env_list = init_env(ms, envp);
	add_var(&ms->env_list, "_", "/usr/bin/minishell", false);
}

void	init_minishell(t_minishell *ms)
{
	ms->cmd_list = NULL;
	ms->tokens_list = NULL;
	ms->env_list = NULL;
	ms->shell_pid = getpid();
	ms->child_pids = 0;
	ms->pipes = NULL;
	ms->pipe_count = 0;
	ms->saved_stdin = -1;
	ms->saved_stdout = -1;
	ms->last_exit_status = 0;
}

char	*handle_input_line(t_minishell *ms)
{
	char	*line;

	signals_handler();
	g_signal = 0;
	line = readline(BLUE "minishell > " RESET);
	if (g_signal == SIGINT)
	{
		ms->last_exit_status = 130;
		g_signal = 0;
	}
	if (!line)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		cleanup_shell(ms, true);
		rl_clear_history();
		exit(ms->last_exit_status);
	}
	return (line);
}

void	process_line(t_minishell *ms, char *line)
{
	if (line[0] == '\0')
		return ;
	add_history(line);
	ms->tokens_list = tokenizer(ms, line);
	if (ms->tokens_list && parsing(ms, ms->tokens_list, &ms->cmd_list))
	{
		free_token_list(&ms->tokens_list);
		if (prepare_heredocs(ms) == -1)
		{
			cleanup_shell(ms, false);
			return ;
		}
		ms->last_exit_status = exec_manager(ms);
	}
	else
		cleanup_shell(ms, false);
}

/* PRINT DEBUG CALLS

print_token(ms.tokens_list);
print_cmds(ms.cmd_list);
dump_open_fds(); // to show open FDs (withoud Valgrind)
dump_all_fds(); // to show all FDs from /proc/self/fd
(including Valgrind) and their details

*/
