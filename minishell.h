/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:59 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 11:59:15 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_SUCCESS 0
# define EXIT_GENERAL_ERROR 1
# define EXIT_SYNTAX_ERROR 2
# define EXIT_CMD_NOT_EXECUTABLE 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131

# define GREEN "\001\033[0;32m\002"
# define BLUE "\001\033[0;36m\002"
# define RESET "\001\033[0m\002"

extern volatile sig_atomic_t	g_signal;

typedef struct s_minishell		t_minishell;

typedef enum e_type
{
	WORD,
	CMD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
}								t_type;

typedef enum e_quotes
{
	UNQUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
}								t_quotes;

typedef struct s_token
{
	t_type						type;
	t_quotes					quotes;
	char						*value;
	bool						quoted;
	t_minishell					*ms;
	struct s_token				*next;
}								t_token;

typedef struct s_redir
{
	t_type						type;
	char						*file;
	bool						quoted_heredoc;
	int							fd;
	t_minishell					*ms;
	struct s_redir				*next;
}								t_redir;

typedef struct s_cmd
{
	char						*cmd;
	char						**args;
	int							index;
	char						*cmd_path;
	t_redir						*redir;
	t_minishell					*ms;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_env
{
	char						*key;
	char						*value;
	bool						exported;
	t_minishell					*ms;
	struct s_env				*next;
}								t_env;

typedef struct s_minishell
{
	t_env						*env_list;
	t_cmd						*cmd_list;
	t_token						*tokens_list;
	int							**pipes;
	int							*child_pids;
	int							pipe_count;
	int							saved_stdin;
	int							saved_stdout;
	pid_t						shell_pid;
	uint8_t						last_exit_status;
}								t_minishell;

/* ----------------- INIT MS ----------------- */
void							init_minishell(t_minishell *ms);
void							init_minishell_env(t_minishell *ms,
									char **envp);
void							init_minishell(t_minishell *ms);
char							*handle_input_line(t_minishell *ms);
void							process_line(t_minishell *ms, char *line);

/* ----------------- SIGNALS ----------------- */
// FOR THE SHELL
int								signals_handler(void);
void							handler_shell(int sig);
// FOR THE HEREDOCS
void							set_signal_handlers_parent_heredoc(void);
void							restore_signal_handlers_parent(void);
void							handler_heredoc_child(int sig);
void							setup_heredoc_child_signals(void);

/* ----------------- PARSING ----------------- */
// TOKENIZER
t_token							*tokenizer(t_minishell *ms, char *line);
bool							handle_word(t_minishell *ms, char *line,
									t_token **tokens, int *i);
void							handle_token(t_minishell *ms, char *line,
									t_token **tokens, int *i);
int								is_space(char c);
int								is_token(char c);
t_token							*new_token(t_minishell *ms, t_type type,
									char *value, bool quoted);
void							add_token(t_token **list, t_token *token);
int								is_empty(const char *str);
void							mini_env(t_minishell *ms, t_env **env);

// QUOTES
int								is_delim(char c);
bool							parse_single_quoted(t_minishell *ms, char *line,
									int *i, char **acc);
bool							return_error(char *mess, char *assembled,
									t_token **tokens);
bool							parse_double_quoted(t_minishell *ms, char *line,
									int *i, char **acc);
bool							parse_unquoted(t_minishell *ms, char *line,
									int *i, char **acc);
char							*append_segment(t_minishell *ms, char **dst,
									char **seg);
char							*str_append_char(t_minishell *ms, char *s,
									char c);
void							handle_unquoted_char(t_minishell *ms,
									char *line, int *i, char **buf);
void							build_unquoted_content(t_minishell *ms,
									char *line, int *i, char **buf);

// EXPANSIONS
void							handle_expansions(t_minishell *ms, char **value,
									t_env **env);
int								count_char(char **tab);
char							*tab_to_str(t_minishell *ms, char **tab);
bool							is_key(t_env **tmp, char *str);
int								count_word(char *str);
char							*itoa_exit_code(t_minishell *ms);
int								is_charset(char c, char *charset);
char							**tf_split(t_minishell *ms, char *str,
									char *charset, int *cmptr);
char							**sep_split(t_minishell *ms, char *s, char *sep,
									int *cmptr);

// PARSER
int								parsing(t_minishell *ms, t_token *token,
									t_cmd **cmd_list);
void							append_cmd(t_cmd **cmd, t_cmd **cmds);
bool							is_redir(t_type type);
void							shift_args(char **args);
void							append_redir(t_cmd **cmd, t_redir *redir);
void							no_cmd(t_cmd **cmd, t_minishell *ms);

// ENVIRONNMENT
t_env							*init_env(t_minishell *ms, char **envp);
int								add_var_shell(t_cmd *cmd, t_env **env);
void							add_node(t_env **list, t_env *env);
t_env							*new_node(t_minishell *ms, char **vars);
void							append_var(t_env *env, char *key, char *value,
									bool exported);

/* ----------------- BUILTINS ----------------- */
int								exec_echo(char **args);
int								exec_cd(t_minishell *ms, t_env **env,
									char **args);
int								exec_env(t_minishell *ms, t_env *env,
									char **args);
int								exec_exit(t_minishell *ms, t_cmd *cmd);
int								exec_export(t_minishell *ms, t_env **env,
									char **args);
char							*get_key(char *s);
bool							var_valid(char *s);
void							add_var(t_env **env, char *key, char *value,
									bool exported);
t_env							*find_node(t_env **env, char *key);
void							print_export(t_env **env);
int								exec_unset(t_env **env, char **args);
int								exec_pwd(t_minishell *ms);

/* ----------------- EXEC ----------------- */
// MANAGER
int								exec_manager(t_minishell *ms);
void							fork_and_execute(t_minishell *ms, int count,
									int **pipes, int *child_pids);
void							directing_child_processes(t_minishell *ms,
									t_cmd *current, int **pipes, int count);
int								wait_for_children(t_minishell *ms, int count,
									int *child_pids);
void							update_last_arg_var(t_minishell *ms,
									t_cmd *cmd);
int								handle_multiple_commands(t_minishell *ms);

// SINGLE COMMANDS
int								handle_single_cmd(t_minishell *ms,
									t_cmd *current);
int								fork_and_exec_single(t_minishell *ms,
									t_cmd *current);
int								exec_builtin_in_parent(t_minishell *ms,
									t_cmd *current);
void							exec_cmd_in_child(t_minishell *ms,
									t_cmd *current);
int								wait_and_get_status(t_minishell *ms, pid_t pid);
bool							does_builtin_need_forking(char *cmd);

// PIPES
void							setup_pipes(t_minishell *ms, int count);
void							close_unused_pipes(t_minishell *ms, int **pipes,
									int count, t_cmd *current);
void							close_all_pipes(int **pipes, int count);

// TYPE OF COMMANDS
bool							is_single_cmd(t_cmd *cmds);
bool							is_first_cmd(t_cmd *cmd);
bool							is_last_cmd(t_cmd *cmd);
bool							is_middle_cmd(t_cmd *cmd);
bool							is_builtin(char *cmd);

// EXECUTION
void							execute_command(t_minishell *ms,
									t_cmd *current_cmd);
int								add_var_shell(t_cmd *cmd, t_env **env);
int								exec_builtin_cmd(t_minishell *ms,
									t_cmd *current_cmd);
int								exec_normal_cmd(t_minishell *ms, t_cmd *cmd);
char							**convert_env_list_to_envp(t_minishell *ms,
									t_env *env_list);

// REDIRECTIONS
int								handle_input_redirection(t_minishell *ms,
									t_cmd *current_cmd);
int								handle_input_file(t_minishell *ms,
									t_redir *redir);
int								handle_output_redirection(t_minishell *ms,
									t_cmd *current_cmd);
int								handle_output_file(t_minishell *ms,
									t_redir *redir);
int								handle_append_file(t_minishell *ms,
									t_redir *redir);

// HEREDOCS
int								prepare_heredocs(t_minishell *ms);
int								handle_cmd_heredocs(t_minishell *ms,
									t_cmd *cmd);
void							process_heredoc_line(t_minishell *ms,
									t_redir *redir, char *line, int pipe_fd);
int								create_heredoc_pipe(t_minishell *ms,
									t_redir *redir, int *pipe_fd);
void							heredoc_child_process(t_minishell *ms,
									t_redir *redir, int *pipe_fd);
int								launch_heredoc_in_child(t_minishell *ms,
									t_redir *redir);
void							close_heredoc_fds(t_minishell *ms);
int								wait_for_heredoc_child(t_minishell *ms,
									pid_t pid, int pipe_read_fd,
									t_redir *redir);
int								handle_heredoc_child_status(t_minishell *ms,
									int status, int pipe_read_fd,
									t_redir *redir);

// GET THE COMMAND PATH
void							get_cmd_path(t_minishell *ms,
									t_cmd *current_cmd);
char							*get_env_value(t_minishell *ms, char *key);
void							reset_cmd_paths(t_minishell *ms);

// UTILS
int								count_elements_in_cmd_lst(t_cmd *cmd_lst);
int								count_elements_in_env_lst(t_env *env_lst);
void							safe_dup2(t_minishell *ms, int oldfd,
									int newfd);
void							safe_close(t_minishell *ms, int *fd);
void							restore_fds(t_minishell *ms);

/* ----------------- MINILIBFT UTILS ----------------- */
int								ft_strcmp(const char *s1, const char *s2);
char							*ft_strjoin_three(t_minishell *ms, char *s1,
									char *s2, char *s3);
int								strict_strcmp(char *s1, char *s2);
int								ft_abs(int nb);
void							*safe_calloc(t_minishell *ms, size_t nmemb,
									size_t size);
char							**safe_split(t_minishell *ms, char const *s,
									char c);
char							*safe_strdup(const char *src, t_minishell *ms);
char							*safe_itoa(t_minishell *ms, int n);
char							*safe_strjoin(t_minishell *ms, char const *s1,
									char const *s2);
char							*safe_substr(t_minishell *ms, char const *s,
									unsigned int start, size_t len);

/* ----------------- ERROR MANAGEMENT ----------------- */
void							error_handler(t_minishell *ms, char **mess,
									int errnum, bool should_exit);
char							**string_array(t_minishell *ms, char *s1,
									char *s2, char *s3);
void							clean_exit(t_minishell *ms, int errnum);
int								errno_to_exit_code(int errnum);
char							*itoa_exit_code(t_minishell *ms);
bool							return_error(char *mess, char *assembled,
									t_token **token_lst);

/* ----------------- CLEANUP FUNCTIONS ----------------- */
void							cleanup_shell(t_minishell *ms, bool clean_env);
void							free_cmd_list(t_cmd **cmd_lst);
void							free_env_list(t_env **env_list);
void							cleanup_pipes(t_minishell *ms);
void							free_pipes(int ***pipes, int count);
void							free_partially_allocated_pipes(int ***pipes,
									int limit);
void							free_redir_list(t_redir **redir);
void							free_token_list(t_token **tokens);
void							free_array_pointer(char ***array);

/* ----------------- DEBUG ----------------- */
// void	print_token(t_token *token);
// void	print_cmds(t_cmd *cmds);
// void	print_env(t_env *env);
// void	print_key(t_env *env, const char *key);
// void	dump_open_fds(void);
// void	dump_all_fds(void);

#endif
