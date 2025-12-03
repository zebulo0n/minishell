/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofayad <ofayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:30:42 by ofayad            #+#    #+#             */
/*   Updated: 2025/11/06 23:30:43 by ofayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("Type : %d, [%s]\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}

// Function to display redirection information
void	print_redir(t_redir *redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	tmp = redir;
	printf("  Redirections:\n");
	while (tmp)
	{
		printf("    Type: ");
		if (tmp->type == INPUT)
			printf("INPUT");
		else if (tmp->type == OUTPUT)
			printf("OUTPUT");
		else if (tmp->type == APPEND)
			printf("APPEND");
		else if (tmp->type == HEREDOC)
			printf("HEREDOC");
		printf(" -> File: [%s]\n", tmp->file);
		tmp = tmp->next;
	}
}

// Function to display command structure
void	print_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	if (!cmds)
	{
		printf("No commands found\n");
		return ;
	}
	tmp = cmds;
	printf("\n===== COMMAND STRUCTURE =====\n");
	while (tmp)
	{
		printf("\nCommand: [%s]\n", tmp->cmd);
		printf("Index: %d\n", tmp->index);
		printf("Arguments:\n");
		i = 0;
		while (tmp->args[i])
		{
			printf("  [%d]: %s\n", i, tmp->args[i]);
			i++;
		}
		print_redir(tmp->redir);
		printf("------------------------\n");
		tmp = tmp->next;
	}
	printf("============================\n\n");
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		else
			printf("%s=\n", env->key);
		env = env->next;
	}
}
void	print_key(t_env *env, const char *key)
{
	if (!env || !key)
		return ;
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
			else
				printf("(null)\n");
			return ;
		}
		env = env->next;
	}
}

 -------- FD DEBUGGING/PRINTING --------


void	dump_open_fds(void)
{
	struct rlimit	rl;
	char			path[256];
	char			buf[256];
	ssize_t			len;
	int				open_count = 0;

	if (getrlimit(RLIMIT_NOFILE, &rl) == -1)
	{
		perror("getrlimit");
		return;
	}

	printf("=== FD DUMP (detailed) ===\n");
	for (int i = 0; i < (int)rl.rlim_cur; i++)
	{
		if (fcntl(i, F_GETFD) != -1)
		{
			snprintf(path, sizeof(path), "/proc/self/fd/%d", i);
			len = readlink(path, buf, sizeof(buf) - 1);
			if (len != -1)
			{
				buf[len] = '\0';
				printf("FD %-3d -> %s", i, buf);

				if (strncmp(buf, "/dev/pts", 8) == 0)
					printf(" [tty]\n");
				else if (strncmp(buf, "pipe:", 5) == 0)
					printf(" [pipe]\n");
				else if (strncmp(buf, "socket:", 7) == 0)
					printf(" [socket]\n");
				else if (strncmp(buf, "/tmp", 4) == 0)
					printf(" [tmpfile]\n");
				else
					printf("\n");
				open_count++;
			}
		}
	}
	printf("Total: %d open FDs\n", open_count);
}

void	dump_all_fds(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			buf[256];
	ssize_t			len;
	char			path[512];
	int				count = 0;
	int				fd;
	int				is_valgrind;

	dir = opendir("/proc/self/fd");
	if (!dir)
		return;
	printf("=== FULL /proc/self/fd DUMP ===\n");
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue;
		snprintf(path, sizeof(path), "/proc/self/fd/%s", entry->d_name);
		len = readlink(path, buf, sizeof(buf) - 1);
		if (len == -1)
			continue;
		buf[len] = '\0';

		fd = atoi(entry->d_name);
		is_valgrind = 0;
		if (strstr(buf, "/tmp/valgrind_") || strstr(buf, "/tmp/vgdb") ||
			strstr(buf, "pipe:[") || fd >= 10240)
			is_valgrind = 1;

		printf("FD %s -> %s", entry->d_name, buf);
		if (is_valgrind)
			printf(" (valgrind)");
		printf("\n");
		count++;
	}
	closedir(dir);
	printf("Total: %d open FDs (including Valgrind internals)\n", count);
}
*/
