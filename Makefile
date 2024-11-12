# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 12:17:59 by flmarsou          #+#    #+#              #
#    Updated: 2024/11/12 13:09:42 by anvacca          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			:=	minishell

# Files
VPATH		:=	src:src/utils:src/lexer:src/parser:src/builtins

SRC			:=	main.c \

SRC_UTILS	:=	ft_perror.c \
				ft_strcpy.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_strlen.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_ismeta.c \
				ft_lstsize.c \
				ft_lstnew.c \
				ft_lstfree.c \
				ft_lstadd_last.c \

SRC_LEXER	:=	tokenizer.c \
				count_tokens.c \

SRC_PARSER	:=	parsing.c \

SRC_CMD		:=	ft_env.c \
				ft_export.c \
				ft_export_print.c \

SOURCES		:=	${SRC} ${SRC_UTILS} ${SRC_LEXER} ${SRC_PARSER} ${SRC_CMD}
OBJ_DIR		:=	obj
OBJECTS		:=	${SOURCES:%.c=${OBJ_DIR}/%.o}

# Variables
CC			:=	cc
CFLAGS		:=  -Iincludes -Wall -Wextra

# Makefile
all:		${EXE}

${EXE}:		${OBJECTS}
			${CC} ${CFLAGS} -lreadline $^ -o $@

${OBJ_DIR}/%.o:	%.c | ${OBJ_DIR}
			${CC} ${CFLAGS} -c $< -o $@

${OBJ_DIR}:
			@mkdir -p $@

clean:
			@rm -rf obj

fclean:		clean
			@rm -rf ${EXE}

re:			fclean all

debug:		re
			rm -rf ${EXE}.log
			./${EXE} 1>&1 2> ${EXE}.log

trace:		re
			rm -rf ${EXE}.log
			strace ./${EXE} 1>&1 2> ${EXE}.log

.PHONY:		all clean fclean re
