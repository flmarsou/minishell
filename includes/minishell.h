/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:17:11 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/17 14:56:29 by anvacca          ###   ########.fr       */
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
# define PATH_MAX		4096

extern unsigned int		g_exit_status;

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
	char			**str;
	t_tokens		*token;
}	t_lexer;

typedef struct s_redir
{
	int				*outfile;
	int				*infile;
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
	int				fd[2];
}	t_parser;

//============================================================================//
//     Source                                                                 //
//============================================================================//

// Free
void			free_lexer(t_lexer *lexer);
void			free_parser(t_parser *parser, unsigned int groups);
void			free_env(char ***env);

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

bool			ft_isalnum(char c);
bool			ft_isalpha(char c);
bool			ft_isdigit(char c);
bool			ft_isprint(char c);
bool			ft_isspace(char c);
bool			ft_ismeta(char c);
bool			ft_strcmp(char *str1, char *str2);
bool			ft_strncmp(char *str1, char *str2, unsigned int size);

unsigned int	ft_strlen(char *str);

//============================================================================//
//     Lexer                                                                  //
//============================================================================//

void			tokenizer(char *input, t_lexer *lexer);
unsigned int	count_tokens(char *str);

//============================================================================//
//     Parser                                                                 //
//============================================================================//

bool			parsing(t_lexer *lexer, t_parser **parser, char **env,
					unsigned int *groups);

bool			handle_quotes_error(t_lexer lexer);

void			handle_quotes(t_lexer *lexer);

bool			handle_pipes_error(t_lexer lexer);

void			handle_dollars(t_lexer *lexer, char **env);

bool			handle_redir_error(t_lexer lexer);

void			realloc_token(t_lexer *lexer, unsigned int y, char **buffer);

void			handle_words(t_lexer *lexer);

void			handle_redir(t_lexer *lexer, t_parser *parser,
					unsigned int groups);
void			handle_command(t_lexer *lexer, t_parser *parser,
					unsigned int groups);

//============================================================================//
//     Execution                                                              //
//============================================================================//

void			handle_fd(t_parser *parser, unsigned int groups, t_redir *redir);

void			exec(t_parser *parser, unsigned int groups, char ***env,
					t_redir *redir);

int				heredoc(char *limiter);

//============================================================================//
//     Builtins                                                               //
//============================================================================//

// bool			ft_cd(char *next_path);

void			ft_echo(char **command, unsigned int argc);

void			ft_env(char **env);

void			ft_export(char ***env, char **input, unsigned int nbr_of_cmd);
void			bubble_sort(char **env);
void			export_swap_vars(char **str1, char **str2);
void			export_print(char *str);
bool			check_input(char *str);
char			**export_copy_arr(char **env);

bool			ft_pwd();

void			ft_unset(char ***env, char **input, unsigned int nbr_of_cmd);

#endif
