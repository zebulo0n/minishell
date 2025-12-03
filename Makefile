###	ARGUMENTS	###
NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror -g3
CC			= cc
DBGFLAGS	= -g3
OBJ_DIR		= obj

LIBFT_DIR 	= libft
LIBFT_A	 	= $(LIBFT_DIR)/libft.a
LIBFT_INC	= $(LIBFT_DIR)

INCLUDES 	= -I $(LIBFT_INC)

###	SOURCES		###
SRCS		= main.c\
			debug.c\
			parsing/tokens.c\
			parsing/tokens_utils.c\
			parsing/word_token.c\
			parsing/handle_quotes.c\
			parsing/quotes_utils.c\
			parsing/parsing_utils.c\
			parsing/parsing.c\
			parsing/env.c\
			parsing/mini_env.c\
			parsing/handle_expansion.c\
			parsing/expansion_utils.c\
			parsing/expansion_split.c\
			parsing/expansion_split_bis.c\
			exit_and_errors/error_handling.c\
			exit_and_errors/last_exit_code.c\
			exec/execution.c\
			exec/get_path.c\
			exec/manager.c\
			exec/pipes.c\
 			exec/redirections_input.c\
 			exec/redirections_output.c\
			exec/waiting.c\
			exec/heredocs.c\
			exec/single_commands.c\
			exec/type_of_cmd.c\
			exec/utils.c\
			exec/safe_functions.c\
			minilibft/utils_not_in_libft.c\
			minilibft/protected_mallocs_1.c\
			minilibft/protected_mallocs_2.c\
			builtins/exec_exit.c\
			builtins/exec_env.c\
			builtins/exec_export.c\
			builtins/print_export.c\
			builtins/exec_unset.c\
			builtins/exec_pwd.c\
			builtins/exec_echo.c\
			builtins/exec_cd.c\
			cleanup/clean_shell.c\
			cleanup/clean_cmds.c\
			cleanup/clean_env.c\
			cleanup/clean_pipes.c\
			cleanup/clean_redirs.c\
			cleanup/clean_tokens.c\
			cleanup/utils.c\
			signal/signal_shell.c\
			signal/signal_heredocs.c\
			
OBJS		= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

###	RULES		###
all	: ${LIBFT_A} ${NAME}

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT_A) -lreadline
	@printf "Compiled ✅\n"

$(LIBFT_A) : 
	$(MAKE) -C $(LIBFT_DIR)

clean	:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	@printf "Clean 🧹\n"

fclean	: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@printf "Big Clean 🧼\n"

re	: fclean all

val :          ### use : make val ARGS="5 800 200 200 7"  
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) ${DBGFLAGS} -o $(NAME)  $(SRCS)  $(LIBFT_A) -lreadline
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS) 

lldb:	
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT_A) -lreadline
	lldb ./$(NAME)


valgr: $(NAME)
	valgrind --tool=memcheck --leak-check=full --track-origins=yes \
		--trace-children=no --track-fds=yes \
		--suppressions=val.supp --log-file=val.log \
		--show-leak-kinds=all ./$(NAME)
	@echo "Valgrind finished. Check val.log for details."

.PHONY	: all clean fclean re val lldb valgr
