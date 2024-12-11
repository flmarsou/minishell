/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:17:11 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/11 15:05:16 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>    // opendir, readdir, closedir
# include <fcntl.h>     // open
# include <signal.h>    // signal, sigaction, sigemptyset, sigaddset, kill
# include <stdio.h>     // printf, perror
# include <stdlib.h>    // malloc, free, exit, getenv
# include <string.h>    // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/wait.h>  // wait, waitpid, wait3, wait4
# include <term.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <termios.h>   // tcsetattr, tcgetattr
# include <unistd.h>    // write, access, read, close, fork
						// getcwd, chdir, unlink, execve, dup
						// dup2, pipe, isatty, ttyname, ttyslot

# include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line
# include <stdbool.h>           // Booleans
								// rl_replace_line, rl_redisplay
# include <readline/history.h>  // add_history

// Debug
# ifndef PRINT_DEBUG
#  define PRINT_DEBUG false
# endif

// Shortcuts
# define STDIN			0
# define STDOUT			1
# define ENV			__environ
# define PATH_MAX		4096

// Colors
# define RESET_COLOR	"\e[0m"
# define ORANGE			"\e[38;2;255;165;0m"

typedef enum e_tokens
{
	SEPARATOR,			// Whitespace
	WORD,				// Others
	SINGLE_QUOTE,		// '
	DOUBLE_QUOTE,		// "
	PIPE,				// |
	INPUT_REDIRECT,		// <
	OUTPUT_REDIRECT,	// >
	HEREDOC,			// <<
	APPEND_REDIRECT,	// >>
	DOLLAR,				// $
	NA_VALUE,			// Equivalent to NULL
}	t_tokens;

typedef struct s_lexer
{
	char				**str;
	t_tokens			*token;
}	t_lexer;

typedef struct s_parser
{
	char			**command;
	unsigned int	nbr_of_commands;
	struct s_redir
	{
		unsigned int	nbr_of_redirs;
		t_tokens		*token;
		char			**type;
	}	redir;
}	t_parser;

typedef struct s_environ
{
	char				*var;
	struct s_environ	*next;
}	t_environ;

//============================================================================//
//     Source                                                                 //
//============================================================================//

void			init_struct(t_environ **environ, t_lexer *lexer);
t_environ		*lstnew_env(char *var);
t_environ		*lstadd_last_env(t_environ **environ, char *input);

// Debug
void			print_lexer(t_lexer lexer);

//============================================================================//
//     Utils                                                                  //
//============================================================================//

void			ft_perror(const unsigned int error);
void			ft_strerror(const char *str);
void			ft_lstfree(t_environ *environ);

char			*ft_strcpy(char *dest, char *src);
char			*ft_strncpy(char *dest, char *src, unsigned int size);
char			*ft_strchr(char *str, char c);
char			*ft_strdup(char *str);

bool			ft_isprint(char c);
bool			ft_isspace(char c);
bool			ft_ismeta(char c);
bool			ft_strcmp(char *str1, char *str2);
bool			ft_strncmp(char *str1, char *str2, unsigned int size);

unsigned int	ft_strlen(char *str);
unsigned int	ft_lstsize(t_environ *environ);

//============================================================================//
//     Lexer                                                                  //
//============================================================================//

void			tokenizer(char *input, t_lexer *lexer);
unsigned int	count_tokens(char *str);

//============================================================================//
//     Parser                                                                 //
//============================================================================//

void			parsing(t_lexer *lexer, t_parser *parser, t_environ environ,
					unsigned int *groups);
/**
 * Checks the placement of quotes in the lexer tokens.
 * Ensures that all quotes are properly opened and closed.
 */
bool			handle_quotes_error(t_lexer lexer);
/**
 * Converts all tokens between quotes into WORD tokens,
 * except for DOLLAR tokens within double quotes.
 */
void			handle_quotes(t_lexer *lexer);
/**
 * Checks the placement of pipes in the lexer tokens.
 */
bool			handle_pipes_error(t_lexer lexer);
/**
 * Expands environment variables in the lexer strings.
 * Replaces DOLLAR to NA_VALUE and changes the following WORD by the
 * corresponding environment variable. Replaces it by NULL if nothing were found.
 */
void			handle_dollars(t_lexer *lexer, t_environ environ);
/**
 * Checks the placement of redirections in the lexer tokens.
 * Ensures that all redirections are followed by a WORD token.
 */
bool			handle_redir_error(t_lexer lexer);

void			destroy_token(t_lexer *lexer, unsigned int y);
void			realloc_token(t_lexer *lexer, unsigned int y, char **buffer);

/**
 * Fuses every WORD tokens next to one another into one, and removes quotes.
 */
void			handle_words(t_lexer *lexer);
/**
 * Populates the parser.redir struct.
 * Removes redirections and their following words from the lexer.
 */
void			handle_redir(t_lexer *lexer, t_parser *parser,
					unsigned int groups);
void			handle_command(t_lexer *lexer, t_parser *parser,
					unsigned int groups);

//============================================================================//
//     Builtins                                                               //
//============================================================================//

void			ft_echo(char **args);
void			ft_env(t_environ *environ);
void			ft_export(t_environ **environ, char *input);
void			ft_export_print(char *str);
void			ft_unset(t_environ **environ, char *input);

#endif
