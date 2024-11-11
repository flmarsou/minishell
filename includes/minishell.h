/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:17:11 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/11 15:48:53 by flmarsou         ###   ########.fr       */
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

// Shortcuts
# define STDIN			0
# define STDOUT			1
# define ENV			__environ
# define PATH_MAX		4096

// Colors
# define RESET_COLOR	"\e[0m"
# define ORANGE			"\e[34m"

typedef struct s_lexer
{
	unsigned char	**str;
	unsigned int	*token;
}	t_lexer;

typedef struct s_parser
{
	unsigned char	**str;
	unsigned int	*token;
}	t_parser;

typedef struct s_environ
{
	unsigned char		*var;
	struct s_environ	*next;
}	t_environ;

typedef enum e_tokens
{
	SEPARATOR,			// Whitespace
	COMMAND,			// Others
	SINGLE_QUOTE,		// '
	DOUBLE_QUOTE,		// "
	PIPE,				// |
	INPUT_REDIRECT,		// <
	OUTPUT_REDIRECT,	// >
	HEREDOC,			// <<
	APPEND_REDIRECT,	// >>
	DOLLAR,				// $
}	t_tokens;

//===============================//
//     Utils                     //
//===============================//

void				ft_perror(const unsigned int error);
void				ft_putstr(unsigned char *str);
void				ft_lstfree(t_environ *environ);

unsigned char		*ft_strcpy(unsigned char *dest, unsigned char *src,
						unsigned int size);

bool				ft_isprint(unsigned char c);
bool				ft_isspace(unsigned char c);
bool				ft_ismeta(unsigned char c);
bool				ft_strncmp(char *str1, char *str2, unsigned int size);

unsigned int		ft_strlen(unsigned char *str);
signed int			ft_strcmp(unsigned char *str1, unsigned char *str2);
unsigned int		ft_lstsize(t_environ *environ);

t_environ			*ft_lstnew(unsigned char *var);

//===============================//
//     Lexer                     //
//===============================//

void				tokenizer(unsigned char *input, t_lexer *lexer);
unsigned int		count_tokens(unsigned char *str);

//===============================//
//     Parser                    //
//===============================//

void				parsing(t_lexer lexer, t_parser *parser);

//===============================//
//     Builtins                  //
//===============================//

void				ft_echo(unsigned char **args);
void				ft_env(t_environ *environ);
void				ft_export(t_environ **environ, unsigned char *var);

#endif
