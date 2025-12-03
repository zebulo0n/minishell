/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:31:48 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/06 23:31:49 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_mess(char **mess, int errnum)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "minishell", 9);
	while (mess && mess[i])
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, mess[i], ft_strlen(mess[i]));
		i++;
	}
	if (errnum > 0)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, strerror(errnum), ft_strlen(strerror(errnum)));
	}
}

void	error_handler(t_minishell *ms, char **mess, int errnum,
		bool should_exit)
{
	int	i;

	if (errnum != 0)
		ms->last_exit_status = errno_to_exit_code(errnum);
	else
	{
		ms->last_exit_status = 1;
	}
	i = 0;
	if (mess && mess[i])
		write_mess(mess, errnum);
	else if (errnum > 0)
	{
		write(STDERR_FILENO, strerror(errnum), ft_strlen(strerror(errnum)));
		write(STDERR_FILENO, "\n", 1);
	}
	free_array_pointer(&mess);
	write(STDERR_FILENO, "\n", 1);
	if (should_exit || ms->shell_pid != getpid())
		clean_exit(ms, ms->last_exit_status);
}

char	**string_array(t_minishell *ms, char *s1, char *s2, char *s3)
{
	char	**array;
	int		cmptr;
	int		i;

	cmptr = 0;
	if (s1 != NULL)
		cmptr++;
	if (s2 != NULL)
		cmptr++;
	if (s3 != NULL)
		cmptr++;
	array = malloc(sizeof(char *) * (cmptr + 1));
	if (!array)
		return (NULL);
	i = 0;
	if (s1 != NULL)
		array[i++] = safe_strdup(s1, ms);
	if (s2 != NULL)
		array[i++] = safe_strdup(s2, ms);
	if (s3 != NULL)
		array[i++] = safe_strdup(s3, ms);
	array[i] = NULL;
	return (array);
}

void	clean_exit(t_minishell *ms, int exit_code)
{
	cleanup_shell(ms, true);
	rl_clear_history();
	exit((u_int8_t)exit_code);
}

int	errno_to_exit_code(int errnum)
{
	if (errnum < 0)
		return (ft_abs(errnum));
	else if (errnum == EACCES)
		return (126);
	else
		return (1);
}
