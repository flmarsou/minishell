/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:39:22 by anvacca           #+#    #+#             */
/*   Updated: 2025/02/10 09:41:00 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Parent Commands:
 *
 * - "ft_env": Prints all the environment variables.
 *   Exit status:
 *   - 0: Success
 *
 * - "ft_export": Adds an environment variable, or prints them in ASCII order.
 *   Exit status:
 *   - 0: Success
 *   - 1: Syntax error
 *
 * - "ft_unset": Removes an environment variable.
 *   Exit status:
 *   - 0: Success
 *
 *
 * Chilren Commands:
 *
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
static int	exec_builtin(char **command, char ***env, unsigned int nbr_of_cmd)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(command[0], "cd"))
		ret = ft_cd(command, nbr_of_cmd, env);
	else if (ft_strcmp(command[0], "echo"))
		ft_echo(command, nbr_of_cmd);
	else if (ft_strcmp(command[0], "pwd"))
		ret = ft_pwd();
	else if (ft_strcmp(command[0], "unset"))
		ft_unset(env, command, nbr_of_cmd);
	else if (ft_strcmp(command[0], "export"))
		ret = ft_export(env, command, nbr_of_cmd);
	else if (ft_strcmp(command[0], "env"))
		ft_env(*env);
	else if (ft_strcmp(command[0], "exit"))
		ft_exit(command, nbr_of_cmd);
	else
		ft_execve(command, *env);
	return (ret);
}

static void	do_exec(t_parser *parser, unsigned int groups, char ***env,
		t_redir *redir)
{
	unsigned int	i;
	int				ret;

	i = 0;
	ret = 0;
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
			do_redirs(&parser[i], redir, i + 1);
			if (parser[i].nbr_of_commands > 0)
				ret = exec_builtin(parser[i].command, env,
						parser[i].nbr_of_commands);
			free_parser(parser, groups);
			exit(ret);
		}
		i++;
	}
}

static void	is_single_builtin(t_parser *parser, t_redir *redir)
{
	if (ft_strcmp(parser[0].command[0], "cd") || ft_strcmp(parser[0].command[0],
			"unset") || ft_strcmp(parser[0].command[0], "export")
		|| ft_strcmp(parser[0].command[0], "env")
		|| ft_strcmp(parser[0].command[0], "exit"))
		do_redirs(&parser[0], redir, 1);
}

static int	single_command(t_parser *parser, char ***env, t_redir *redir,
				int *status)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN);
	fd_out = dup(STDOUT);
	is_single_builtin(parser, redir);
	if (ft_strcmp(parser[0].command[0], "cd"))
		*status = ft_cd(parser[0].command, parser[0].nbr_of_commands, env);
	else if (ft_strcmp(parser[0].command[0], "unset"))
		ft_unset(env, parser[0].command, parser[0].nbr_of_commands);
	else if (ft_strcmp(parser[0].command[0], "export"))
		*status = ft_export(env, parser[0].command, parser[0].nbr_of_commands);
	else if (ft_strcmp(parser[0].command[0], "env"))
		ft_env(*env);
	else if (ft_strcmp(parser[0].command[0], "exit"))
		*status = ft_exit(parser[0].command, parser[0].nbr_of_commands);
	else
		return (666);
	dup2(fd_in, STDIN);
	dup2(fd_out, STDOUT);
	return (unlinker(redir), *status);
}

int	exec(t_parser *parser, unsigned int groups, char ***env, t_redir *redir)
{
	unsigned int	i;
	int				status;

	i = 0;
	status = 0;
	redir->nbr_of_outfile = 0;
	redir->nbr_of_infile = 0;
	init_pipes(parser, groups);
	signal(SIGQUIT, handle_signal_child_kill);
	if (!do_heredoc(parser, redir, groups, *env))
		return (130);
	if (groups == 1 && parser[0].nbr_of_commands > 0 && single_command(parser,
			env, redir, &status) != 666)
		return (status);
	signal(SIGINT, handle_signal_child);
	do_exec(parser, groups, env, redir);
	close_unused_pipes(parser, groups, -1);
	while (i < groups)
	{
		waitpid(parser[i].pid, &status, 0);
		i++;
	}
	signal(SIGINT, handle_signal);
	unlinker(redir);
	return (status / 256);
}
