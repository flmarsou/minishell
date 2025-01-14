/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:17:11 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/06 15:19:59 by anvacca          ###   ########.fr       */
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
	END,
}	t_tokens;

typedef struct s_lexer
{
	char				**str;
	t_tokens			*token;
}	t_lexer;

 typedef struct s_redir
{
	int					*outfile;
	int					*infile;
	unsigned int	nbr_of_outfile;
	unsigned int	nbr_of_infile;
}	t_redir;

typedef struct s_parser
{
	char			**command;
	unsigned int	nbr_of_commands;
	unsigned int	nbr_of_redirs;
	t_tokens		*token;
	char			**type;
}	t_parser;

typedef struct s_environ
{
	char				*var;
	struct s_environ	*next;
}	t_environ;

//============================================================================//
//     Source                                                                 //
//============================================================================//

void			free_lexer(t_lexer *lexer);
void			free_parser(t_parser *parser, unsigned int groups);
void			free_env(t_environ *environ);

// Debug
void			print_lexer(t_lexer lexer);
void			print_parser(t_parser *parser, unsigned int groups);

//============================================================================//
//     Utils                                                                  //
//============================================================================//

void			ft_perror(const unsigned int error);
void			ft_strerror(const char *str);
void			ft_putstr(char *str);

char			*ft_strcpy(char *dest, char *src);
char			*ft_strncpy(char *dest, char *src, unsigned int size);
char			*ft_strchr(char *str, char c);
char			*ft_strdup(char *str);
char			*ft_itoa(int nbr);
char			*ft_strjoin(char *str1, char *str2);

bool			ft_isprint(char c);
bool			ft_isspace(char c);
bool			ft_ismeta(char c);
bool			ft_strcmp(char *str1, char *str2);
bool			ft_strncmp(char *str1, char *str2, unsigned int size);

unsigned int	ft_strlen(char *str);
unsigned int	ft_lstsize(t_environ *environ);

t_environ		*lstnew_env(char *var);
void			lstadd_last_env(t_environ **environ, char *input);

//============================================================================//
//     Lexer                                                                  //
//============================================================================//

void			tokenizer(char *input, t_lexer *lexer);
unsigned int	count_tokens(char *str);

//============================================================================//
//     Parser                                                                 //
//============================================================================//

bool			parsing(t_lexer *lexer, t_parser **parser, t_environ environ,
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
//     Execution                                                              //
//============================================================================//

void	handle_fd(t_parser *parser, unsigned int groups, t_redir *redir);

void	exec(t_parser *parser, unsigned int groups, t_environ **environ,
		t_redir *redir);

int		heredoc(char *limiter);

//============================================================================//
//     Builtins                                                               //
//============================================================================//

// bool			ft_cd(char *next_path);
void			ft_echo(char **args, unsigned int argc);
void			ft_env(t_environ *environ);
void			ft_export(t_environ **environ, char **input, unsigned int nbr_of_cmd);
void			ft_export_print(char *str);
bool			ft_pwd();
void			ft_unset(t_environ **environ, char *input);

#endif
