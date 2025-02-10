/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:17:11 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/10 10:40:40 by flmarsou         ###   ########.fr       */
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
# define STDIN	0
# define STDOUT	1
# define ERR	"\e[1;31m[x] - Error: \e[0m"
# define SERR	"\e[1;31m[x] - Syntax Error: \e[0m"
# define WARN	"\e[1;35m[!] - Warning: \e[0m"

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
	END
}					t_tokens;

typedef struct s_lexer
{
	char			**str;
	t_tokens		*token;
	int				exit_status;
}					t_lexer;

typedef struct s_parser
{
	char			**command;
	unsigned int	nbr_of_commands;
	unsigned int	nbr_of_redirs;
	t_tokens		*token;
	char			**type;
	int				fd[2];
	pid_t			pid;
}					t_parser;

typedef struct s_redir
{
	int				*outfile;
	int				*infile;
	unsigned int	nbr_of_outfile;
	unsigned int	nbr_of_infile;
}					t_redir;

//============================================================================//
//     Source                                                                 //
//============================================================================//

// Free
void				free_lexer(t_lexer *lexer);
void				free_parser(t_parser *parser, unsigned int groups);
void				free_env(char ***env);

// Debug
void				print_lexer(t_lexer lexer);
void				print_parser(t_parser *parser, unsigned int groups);

//============================================================================//
//     Utils                                                                  //
//============================================================================//

void				ft_perror(const unsigned int error);
void				ft_putstr(char *str);
void				ft_putstr_fd(char *str, int fd);

char				*ft_strcpy(char *dest, char *src);
char				*ft_strcat(char *dest, char *src);
char				*ft_strncpy(char *dest, char *src, unsigned int size);
char				*ft_strchr(char *str, char c);
char				*ft_strdup(char *str);
char				*ft_strjoin(char *str1, char *str2);
char				*ft_itoa(int nbr);

bool				ft_isalnum(char c);
bool				ft_isalpha(char c);
bool				ft_isdigit(char c);
bool				ft_isprint(char c);
bool				ft_isspace(char c);
bool				ft_ismeta(char c);
bool				ft_strcmp(char *str1, char *str2);
bool				ft_strncmp(char *str1, char *str2, unsigned int size);

unsigned int		ft_strlen(char *str);

long				ft_atol(char *str);

//============================================================================//
//     Lexer                                                                  //
//============================================================================//

/**
 * @brief Tokenizes the input string and stores the tokens in the lexer.
 * 
 * Processes the given input string character by character,
 * identifying different types of tokens (e.g., separators,
 * quotes, pipes, redirections, ...) and stores them in the provided
 * lexer structure for further processing.
 * 
 * @param input Input string to be tokenized.
 * @param lexer Lexer structure where the tokens will be stored.
 */
void				tokenizer(char *input, t_lexer *lexer);

/**
 * Counts the number of tokens in a given string for allocation.
 */
unsigned int		count_tokens(char *str);

//============================================================================//
//     Parser Functions                                                       //
//============================================================================//

/**
 * @brief Parses the tokens from the lexer and builds the parser structure.
 * 
 * @param lexer Lexer structure containing the tokenized input.
 * @param parser Parser structures (array) to be populated with parsed data.
 * @param env Environment variables to be used for variable expansion.
 * @param groups Sets the number of groups for handling pipe-related commands.
 * 
 * @return True if parsing was successful, false otherwise.
 */
bool				parsing(t_lexer *lexer, t_parser **parser, char **env,
						unsigned int *groups);

/**
 * Searches for a variable in the environment.
 * 
 * @return Value of the variable if found, NULL otherwise.
 */
char				*find_in_env(char *var, char **env);

/**
 * Swaps current token for `src`, and turns it to a WORD token.
 */
void				realloc_token(t_lexer *lexer, unsigned int y, char **src);

/**
 * Checks if every opening quote has a matching closing quote.
 */
bool				handle_quotes_error(t_lexer lexer);

/**
 * Processes tokens within quotes, converting them into WORD tokens,
 * except for DOLLAR tokens inside SINGLE_QUOTE quotes which are handled later.
 */
void				handle_quotes(t_lexer *lexer);

/**
 * Checks if every PIPE tokens have a WORD token before and after themselves.
 */
bool				handle_pipes_error(t_lexer lexer);

/**
 * @brief Expands dollar-prefixed variables with the following rules:
 * 
 * - Dollar after a HEREDOC:
 * 		No expansion is performed.
 * 
 * - Dollar followed by a WORD beginning with a digit:
 * 		No expansion occurs, and the digit is removed.
 * 
 * - Dollar followed by a SEPARATOR:
 * 		The DOLLAR token is turned into a WORD token.
 * 
 * - Dollar followed by a WORD beginning with '?':
 * 		The question mark is expanded to the exit status.
 * 
 * - Dollar followed by a WORD:
 * 		Attempts to expand the variable.
 * 		If no match is found, the token is nullified.
 */
void				handle_dollars(t_lexer *lexer, char **env);

/**
 * Checks if redirection symbols (e.g., >, <) are followed by a WORD token.
 */
bool				handle_redir_error(t_lexer lexer);

/**
 * @brief Merges WORD tokens within quotes and across token boundaries.
 * 
 * - Merges multiple consecutive WORD tokens inside quotes into one token.
 * 
 * - Merges adjacent WORD tokens that are not separated by
 *   SEPARATOR or redirections.
 */
void				handle_words(t_lexer *lexer);

/**
 * @brief Processes redirection tokens and organizes them within the parser.
 *
 * Redirection tokens (e.g., >, <) are stored in the parser structure,
 * grouping them according to their respective pipe group,
 * nullifying the tokens once processed.
 */
void				handle_redir(t_lexer *lexer, t_parser *parser,
						unsigned int groups);

/**
 * @brief Processes command tokens and organizes them within the parser.
 *
 * WORD tokens are stored in the parser structure,
 * grouping them according to their respective pipe group.
 */
void				handle_command(t_lexer *lexer, t_parser *parser,
						unsigned int groups);

//============================================================================//
//     Execution                                                              //
//============================================================================//

int					exec(t_parser *parser, unsigned int groups, char ***env,
						t_redir *redir);

void				heredoc(char *limiter, bool *leave, unsigned int count,
						char **env);

void				do_redirs(t_parser *parser, t_redir *redir, unsigned int i);
void				count_redir(t_parser *parser, t_redir *redir);

void				handle_signal(int sig);
void				handle_signal_child(int sig);
void				handle_signal_child_kill(int sig);

bool				do_heredoc(t_parser *parser, t_redir *redir,
						unsigned int groups, char **env);
void				handle_signal_h(int sig);
void				unlinker(t_redir *redir);

void				init_pipes(t_parser *parser, unsigned int groups);
void				close_unused_pipes(t_parser *parser, unsigned int groups,
						unsigned int i);
void				pipes(t_parser *parser, unsigned int groups,
						unsigned int i);

//============================================================================//
//     Builtins                                                               //
//============================================================================//

bool				ft_cd(char **command, unsigned int nbr_of_cmd, char ***env);

void				ft_echo(char **command, unsigned int nbr_of_cmd);

void				ft_env(char **env);

void				ft_execve(char **command, char **env);

bool				ft_exit(char **command, unsigned int nbr_of_cmd);

bool				ft_export(char ***env, char **input,
						unsigned int nbr_of_cmd);
char				**export_copy_arr(char **env);				// Copy
void				bubble_sort(char **env);					// Sort
void				export_swap_vars(char **str1, char **str2);	// Swap
void				export_print(char *str);					// Print

bool				ft_pwd(void);

void				ft_unset(char ***env, char **input,
						unsigned int nbr_of_cmd);

#endif
