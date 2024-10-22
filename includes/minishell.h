/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:17:11 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/21 15:11:57 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>		// printf, perror
# include <stdlib.h>	// malloc, free, exit, getenv
# include <string.h>	// strerror
# include <sys/wait.h>	// wait, waitpid, wait3, wait4
# include <signal.h>	// signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>	// stat, lstat, fstat
# include <fcntl.h>		// open
# include <dirent.h>	// opendir, readdir, closedir
# include <sys/ioctl.h>	// ioctl
# include <termios.h>	// tcsetattr, tcgetattr
# include <term.h>		// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <unistd.h>	// write, access, read, close, fork
						// getcwd, chdir, unlink, execve, dup
						// dup2, pipe, isatty, ttyname, ttyslot

# include <stdbool.h>	// Booleans

# include <readline/readline.h>	// readline, rl_clear_history, rl_on_new_line
								// rl_replace_line, rl_redisplay
# include <readline/history.h>	// add_history

# define ENV	__environ
# define STDIN	0
# define STDOUT	1

# define CTRL_C	3
# define CTRL_D	4
# define ENTER	10

# define ORANGE			"\e[34m"
# define RESET_COLOR	"\e[0m"

typedef struct s_input
{
	unsigned char	*buffer;
	unsigned int	length;
}	t_input;

typedef struct s_lexer
{
	unsigned char	*str;
	unsigned int	token;
	struct s_lexer	*next;
}	t_lexer;

typedef enum e_tokens
{
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

void			ft_perror(const unsigned int error);
unsigned char	*ft_realloc(unsigned char *old_str, unsigned int old_size, unsigned int new_size);
unsigned char	*ft_strcpy(unsigned char *dest, unsigned char *src, unsigned int size);
void			ft_putstr(unsigned char *str);
bool			ft_isprint(unsigned char c);

//===============================//
//     Input                     //
//===============================//

void			enable_raw_mode(struct termios *orig_termios);
void			disable_raw_mode(struct termios *orig_termios);

void			read_user_input();

//===============================//
//     Lexer                     //
//===============================//

void			tokenizer(unsigned char *input);

//===============================//
//     Builtins                  //
//===============================//

void			ft_echo(unsigned char **args);

#endif
