# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 12:17:59 by flmarsou          #+#    #+#              #
#    Updated: 2024/10/11 15:02:23 by flmarsou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			:=	minishell

# Files
VPATH		:=	src

SRC			:=	main.c \

SRC_UTILS	:=	ft_perror.c \
				ft_realloc.c \

SOURCES		:=	${SRC}
OBJ_DIR		:=	obj
OBJECTS		:=	${SOURCES:%.c=${OBJ_DIR}/%.o}

# Variables
CC			:=	cc
CFLAGS		:=  -Iincludes -Wall -Wextra -fsanitize=address,leak

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
