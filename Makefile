# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 12:17:59 by flmarsou          #+#    #+#              #
#    Updated: 2024/10/31 13:52:22 by flmarsou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			:=	minishell

# Files
VPATH		:=	src:src/utils:src/terminal:src/lexer

SRC			:=	main.c \

SRC_UTILS	:=	ft_perror.c \
				ft_realloc.c \
				ft_strcpy.c \
				ft_strmove.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_ismeta.c \

SRC_TERM	:=	raw_mode.c \
				get_terminal_size.c \
				read_user_input.c \
				edit_user_input.c \
				arrow_keys.c \

SRC_LEXER	:=	tokenizer.c \
				count_tokens.c \

SOURCES		:=	${SRC} ${SRC_UTILS} ${SRC_TERM} ${SRC_LEXER}
OBJ_DIR		:=	obj
OBJECTS		:=	${SOURCES:%.c=${OBJ_DIR}/%.o}

# Variables
CC			:=	cc
CFLAGS		:=  -Iincludes -Wall -Wextra

# Makefile
all:		${EXE}

${EXE}:		${OBJECTS}
			${CC} ${CFLAGS} $^ -o $@

${OBJ_DIR}/%.o:	%.c | ${OBJ_DIR}
			${CC} ${CFLAGS} -c $< -o $@

${OBJ_DIR}:
			@mkdir -p $@

clean:
			@rm -rf obj

fclean:		clean
			@rm -rf ${EXE}

re:			fclean all

.PHONY:		all clean fclean re
