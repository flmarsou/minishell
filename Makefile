# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 12:17:59 by flmarsou          #+#    #+#              #
#    Updated: 2024/11/08 15:03:04 by flmarsou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			:=	minishell

# Files
VPATH		:=	src:src/utils:src/lexer

SRC			:=	main.c \

SRC_UTILS	:=	ft_perror.c \
				ft_strcpy.c \
				ft_strncmp.c \
				ft_strlen.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_ismeta.c \

SRC_LEXER	:=	tokenizer.c \
				count_tokens.c \

SOURCES		:=	${SRC} ${SRC_UTILS} ${SRC_LEXER}
OBJ_DIR		:=	obj
OBJECTS		:=	${SOURCES:%.c=${OBJ_DIR}/%.o}

# Variables
CC			:=	cc
CFLAGS		:=  -Iincludes -Wall -Wextra -fsanitize=address,leak -g

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
