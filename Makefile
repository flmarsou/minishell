# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 12:17:59 by flmarsou          #+#    #+#              #
#    Updated: 2025/02/10 08:59:33 by flmarsou         ###   ########.fr        #
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

SRC_UTILS	:=	ft_atol.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isdigit.c \
				ft_ismeta.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_itoa.c \
				ft_perror.c \
				ft_putstr_fd.c \
				ft_putstr.c \
				ft_strchr.c \
				ft_strcat.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strncpy.c \

SRC_LEXER	:=	tokenizer.c \
				count_tokens.c \

SRC_PARSER	:=	parsing.c \
				parser_utils.c \
				handle_quotes_error.c \
				handle_quotes.c \
				handle_pipes_error.c \
				handle_dollars.c \
				handle_redir_error.c \
				handle_words.c \
				handle_redir.c \
				handle_command.c \

SRC_EXEC	:=	exec.c \
				handle_child_signals.c \
				handle_heredoc.c \
				handle_pipes.c \
				handle_redirs.c \
				heredoc.c \
				heredoc_signal.c \

SRC_CMD		:=	ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_execve.c \
				ft_exit.c \
				ft_export.c \
				ft_export_utils.c \
				ft_pwd.c \
				ft_unset.c \

SOURCES		:=	${SRC} ${SRC_UTILS} ${SRC_LEXER} ${SRC_PARSER} ${SRC_EXEC} ${SRC_CMD}
OBJ_DIR		:=	obj
OBJECTS		:=	${SOURCES:%.c=${OBJ_DIR}/%.o}

# Variables
CC			:=	cc
CFLAGS		:=  -Iincludes -O2 -Wall -Wextra -fsanitize=address -g3

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
