/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:17:11 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/09 15:15:17 by flmarsou         ###   ########.fr       */
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

# include <readline/readline.h>	// readline, rl_clear_history, rl_on_new_line
								// rl_replace_line, rl_redisplay
# include <readline/history.h>	// add_history

typedef enum e_tokens
{
	SINGLE_QUOTE,		// '
	DOUBLE_QUOTE,		// "
	PIPE,				// |
	INPUT_REDIRECT,		// <
	OUTPUT_REDIRECT,	// >
	HEREDOC,			// <<
	APPEND_REDIRECT,	// >>
}	t_tokens;

#endif