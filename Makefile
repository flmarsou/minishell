# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 12:17:59 by flmarsou          #+#    #+#              #
#    Updated: 2024/12/24 14:31:12 by flmarsou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			:=	minishell

# Files
VPATH		:=	src \
				src/utils \
				src/lexer \
				src/parser \
				src/execution \
				src/builtins \

SRC			:=	main.c \
				free.c \
				debug.c \

SRC_UTILS	:=	ft_ismeta.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_itoa.c \
				ft_lstsize.c \
				ft_perror.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdup.c \
				ft_strerror.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strncpy.c \
				lstadd_last_env.c \
				lstnew_env.c \

SRC_LEXER	:=	tokenizer.c \
				count_tokens.c \

SRC_PARSER	:=	parsing.c \
				handle_quotes_error.c \
				handle_quotes.c \
				handle_pipes_error.c \
				handle_dollars.c \
				handle_redir_error.c \
				_realloc_token.c \
				handle_words.c \
				handle_redir.c \
				handle_command.c \

SRC_EXEC	:=	handle_fd.c \
				heredoc.c \

SRC_CMD		:=	ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_export.c \
				ft_export_print.c \
				ft_pwd.c \
				ft_unset.c \

SOURCES		:=	${SRC} ${SRC_UTILS} ${SRC_LEXER} ${SRC_PARSER} ${SRC_EXEC}
OBJ_DIR		:=	obj
OBJECTS		:=	${SOURCES:%.c=${OBJ_DIR}/%.o}

# Variables
CC			:=	cc
CFLAGS		:=  -Iincludes -O2 -Wall -Wextra

# Makefile
all:		${EXE}

${EXE}:		${OBJECTS}
			@${CC} ${CFLAGS} -lreadline $^ -o $@

${OBJ_DIR}/%.o:	%.c | ${OBJ_DIR}
			@${CC} ${CFLAGS} -c $< -o $@

${OBJ_DIR}:
			@mkdir -p $@

clean:
			@rm -rf obj

fclean:		clean
			@rm -rf ${EXE} ${EXE}.log

re:			fclean all

debug:		CFLAGS += -D PRINT_DEBUG=true
debug:		re
			@echo "Running the program in debug mode..."
			@./${EXE} 1>&1 2> ${EXE}.log

trace:		re
			strace ./${EXE} 1>&1 2> ${EXE}.log

.PHONY:		all clean fclean re
