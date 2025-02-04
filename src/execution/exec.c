/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:39:22 by anvacca           #+#    #+#             */
/*   Updated: 2025/02/04 10:10:10 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_name(unsigned int i)
{
	char	*ret;
	char	*itoa;

	itoa = ft_itoa(i++);
	ret = ft_strjoin(".heredoc_", itoa);
	free(itoa);
	return (ret);
}

static void	count_redirs(t_parser *parser, t_redir *redir)
{
	unsigned int	i;

	redir->nbr_of_outfile = 0;
	redir->nbr_of_infile = 0;
	i = 0;
	while (i < parser->nbr_of_redirs)
	{
		if (parser->token[i] == OUTPUT_REDIRECT
			|| parser->token[i] == APPEND_REDIRECT)
			redir->nbr_of_outfile++;
		if (parser->token[i] == INPUT_REDIRECT || parser->token[i] == HEREDOC)
			redir->nbr_of_infile++;
		i++;
	}
}

static void	unlinker(t_redir *redir)
{
	static unsigned int	i = 1;
	unsigned int		j;
	char				*str;

	j = 0;
	i += redir->nbr_of_infile;
	while (j < i)
	{
		str = heredoc_name(j);
		unlink(str);
		free(str);
		j++;
	}
}

/**
 * - "ft_cd": Changes the current working directory.
 *   Exit values:
 *   - 0: Success
 *   - 1: Failure (directory not found)
 *
 * - "ft_echo": Prints arguments to the standard output.
 *   Exit values:
 *   - 0: Success
 *
 * - "ft_pwd": Prints the current working directory.
 *   Exit values:
 *   - 0: Success
 *   - 1: Failure (if getcwd fails)
 *
 * - "ft_exit": Exits the program.
 *   Exit values:
 *   - 0: Success
 *   - 2: Invalid input
 *   - 1-255: Valid input
 *
 * - "ft_execve": Non built-in command.
 *   Exit values:
 *   - 0: Success
 *   - 127: Command not found or not executable
 */
void	exec_builtin(char **command, char ***env, unsigned int nbr_of_cmd)
{
	unsigned int	i;

	i = 1;
	if (nbr_of_cmd < 1)
		return ;
	// if (ft_strcmp(command[0], "cd"))
	// 	ft_cd(command[i]);
	if (ft_strcmp(command[0], "echo"))
		ft_echo(command, nbr_of_cmd);
	else if (ft_strcmp(command[0], "pwd"))
		ft_pwd();
	else if (ft_strcmp(command[0], "unset"))
		ft_unset(env, command, nbr_of_cmd);
	else if (ft_strcmp(command[0], "export"))
		ft_export(env, command, nbr_of_cmd);
	else if (ft_strcmp(command[0], "env"))
		ft_env(*env);
	else if (ft_strcmp(command[0], "exit"))
		ft_exit(command, nbr_of_cmd);
	else
		ft_execve(command, *env);
	return ;
}

void	do_outfile(t_parser *parser, t_redir *redir)
{
	unsigned int	i;
	int				fd;

	i = 0;
	while (i < redir->nbr_of_outfile)
	{
		if (parser->token[i] == OUTPUT_REDIRECT)
			fd = open(parser->type[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (parser->token[i] == APPEND_REDIRECT)
			fd = open(parser->type[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT);
		close(fd);
		i++;
	}
}

static char	*handle_name(bool reset)
{
	static unsigned int	i = 1;
	char				*ret;
	char				*itoa;

	if (reset == false)
	{
		i = 1;
		return (NULL);
	}
	itoa = ft_itoa(i++);
	ret = ft_strjoin(".heredoc_", itoa);
	free(itoa);
	return (ret);
}

static void	do_infile(t_parser *parser, t_redir *redir)
{
	unsigned int	j;
	int				fd;
	char			*name;

	j = 0;
	while (j < redir->nbr_of_infile)
	{
		if (parser->token[j] == HEREDOC)
		{
			name = handle_name(true);
			fd = open(name, O_RDONLY);
			free(name);
		}
		if (parser->token[j] == INPUT_REDIRECT)
		{
			fd = open(parser->type[j], O_RDONLY);
		}
		if (parser->nbr_of_commands > 0)
			dup2(fd, STDIN);
		if (redir->nbr_of_outfile > 0)
			do_outfile(parser, redir);
		close(fd);
		j++;
	}
}

void	do_exec(t_parser *parser, t_redir *redir)
{
	if (parser->nbr_of_redirs > 0)
	{
		count_redirs(parser, redir);
		if (redir->nbr_of_infile > 0)
		{
			do_infile(parser, redir);
		}
		else if (redir->nbr_of_outfile > 0)
			do_outfile(parser, redir);
	}
}

void	handle_signal_child(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDOUT, "\n", 1);
		rl_redisplay();
	}
}

void	handle_signal_child_kill(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(STDOUT, "Quit (core dumped)\n", 19);
	rl_redisplay();
}

void	init_pipes(t_parser *parser, unsigned int groups)
{
	unsigned int	i;

	i = 0;
	while (i < groups - 1)
	{
		pipe(parser[i].fd);
		i++;
	}
}

void	close_unused_pipes(t_parser *parser, unsigned int groups,
		unsigned int i)
{
	unsigned int	j;

	j = 0;
	while (j < groups - 1)
	{
		if (j == i)
			close(parser[j].fd[0]);
		else if (j == i - 1)
			close(parser[j].fd[1]);
		else
		{
			close(parser[j].fd[0]);
			close(parser[j].fd[1]);
		}
		j++;
	}
}

void	pipes(t_parser *parser, unsigned int groups, unsigned int i)
{
	if (i == 0)
	{
		dup2(parser[i].fd[1], STDOUT);
		close(parser[i].fd[1]);
	}
	else if (i < groups - 1)
	{
		close(parser[i].fd[0]);
		dup2(parser[i - 1].fd[0], STDIN);
		close(parser[i - 1].fd[0]);
		dup2(parser[i].fd[1], STDOUT);
		close(parser[i].fd[1]);
	}
	else
	{
		dup2(parser[i - 1].fd[0], STDIN);
		close(parser[i - 1].fd[0]);
	}
}


bool	do_heredoc(t_parser *parser, t_redir *redir, unsigned int groups)
{
	unsigned int	j;
	unsigned int	i;
	unsigned int	count;
	bool			leave;

	j = 0;
	i = 0;
	leave = true;
	count = 1;
	while (i < groups)
	{
		count_redirs(&parser[i], redir);
		while (j < redir->nbr_of_infile)
		{
			if (parser[i].token[j] == HEREDOC)
			{
				signal(SIGINT, SIG_IGN);
				heredoc(parser[i].type[j], &leave, count);
				count++;
				if (leave == false)
					return (leave);
			}
			j++;
		}
		i++;
	}
	return (leave);
}

void	exec(t_parser *parser, unsigned int groups, char ***env, t_redir *redir)
{
	unsigned int	i;
	int				status;

	i = 0;
	redir->nbr_of_outfile = 0;
	redir->nbr_of_infile = 0;
	init_pipes(parser, groups);
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_signal_child_kill);
	if (do_heredoc(parser, redir, groups) == false)
		return ;
	while (i < groups)
	{
		parser[i].pid = fork();
		if (parser[i].pid == 0)
		{
			if (groups > 1)
			{
				close_unused_pipes(parser, groups, i);
				pipes(parser, groups, i);
			}
			do_exec(&parser[i], redir);
			if (parser[i].nbr_of_commands > 0)
				exec_builtin(parser[i].command, env, parser[i].nbr_of_commands);
			free_parser(parser, groups);
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < groups - 1)
	{
		close(parser[i].fd[0]);
		close(parser[i].fd[1]);
		i++;
	}
	i = 0;
	while (i < groups)
	{
		waitpid(parser[i].pid, &status, 0);
		i++;
	}
	signal(SIGINT, handle_signal);
	g_exit_status = status / 256;
	unlinker(redir);
}
