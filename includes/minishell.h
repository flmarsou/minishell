/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:17:11 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/25 12:26:48 by anvacca          ###   ########.fr       */
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

# define ENV __environ
# define STDIN 0
# define STDOUT 1

# define CTRL_C 3
# define CTRL_D 4
# define ENTER 10
# define BACKSPACE 127

# define ORANGE "\e[34m"
# define RESET_COLOR "\e[0m"

typedef struct s_input
{
	unsigned char	*buffer;
	unsigned int	len;
	unsigned int	cursor_pos;
}					t_input;

typedef struct s_lexer
{
	unsigned char	*str;
	unsigned int	token;
}					t_lexer;

typedef enum e_tokens
{
	SEPARATOR, // Whitespace
	COMMAND, // Others
	SINGLE_QUOTE, // '
	DOUBLE_QUOTE, // "
	PIPE, // |
	INPUT_REDIRECT, // <
	OUTPUT_REDIRECT, // >
	HEREDOC, // <<
	APPEND_REDIRECT, // >>
	DOLLAR, // $
}					t_tokens;

//===============================//
//     Utils                     //
//===============================//

void				ft_perror(const unsigned int error);
unsigned char		*ft_realloc(unsigned char *old_str, unsigned int old_size,
						unsigned int new_size);
unsigned char		*ft_strcpy(unsigned char *dest, unsigned char *src,
						unsigned int size);
void				ft_putstr(unsigned char *str);
bool				ft_isprint(unsigned char c);
bool				ft_isspace(unsigned char c);
bool				ft_ismeta(unsigned char c);

//===============================//
//     Input                     //
//===============================//

void				enable_raw_mode(struct termios *orig_termios);
void				disable_raw_mode(struct termios *orig_termios);

void				read_user_input(t_input *input);

void				handle_input(t_input *input, unsigned char character);
void				handle_backspace(t_input *input);
void				handle_delete(t_input *input);

//===============================//
//     Lexer                     //
//===============================//

void				tokenizer(unsigned char *input);
unsigned int		count_tokens(unsigned char *str);

//===============================//
//     Builtins                  //
//===============================//

void				ft_echo(unsigned char **args);

#endif
