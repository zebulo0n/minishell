# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoeschne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 18:54:33 by zoeschne          #+#    #+#              #
#    Updated: 2025/05/05 16:02:45 by zoeschne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###	ARGUMENTS	###
NAME	= libft.a
CFLAGS	= -Wall -Werror -Wextra
CC	= cc

###	SOURCES		###
SRCS	= ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c 

OBJS	= $(SRCS:.c=.o)

BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJS	= $(BONUS:.c=.o)

###	RULES		###
all : ${NAME}

${NAME} : ${OBJS}
	 ar rcs ${NAME} ${OBJS}

##	%.o : %.c
##	${CC} ${CFLAGS} -I includes -c $< -o $@

bonus : ${OBJS} ${BONUS_OBJS}
	ar rcs ${NAME} ${OBJS} ${BONUS_OBJS}
clean :
	rm -f ${OBJS} ${BONUS_OBJS}

fclean : clean 
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re
