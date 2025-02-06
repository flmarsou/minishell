/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:39:22 by anvacca           #+#    #+#             */
/*   Updated: 2025/02/06 09:19:57 by flmarsou         ###   ########.fr       */
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
void	exec_builtin(char **command, char ***env, unsigned int nbr_of_cmd)
{
	unsigned int	i;

	i = 1;
	if (nbr_of_cmd < 1)
		return ;
	if (ft_strcmp(command[0], "cd"))
		ft_cd(command, nbr_of_cmd, env);
	else if (ft_strcmp(command[0], "echo"))
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

void	do_exec(t_parser *parser, unsigned int groups, char ***env,
		t_redir *redir)
{
	unsigned int	i;

	i = 0;
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
			do_redirs(&parser[i], redir);
			if (parser[i].nbr_of_commands > 0)
				exec_builtin(parser[i].command, env, parser[i].nbr_of_commands);
			free_parser(parser, groups);
			exit(0);
		}
		i++;
	}
}

bool	single_command(t_parser *parser, unsigned int groups, char ***env, t_redir *redir)
{
	unsigned int	i;

	i = 0;
	if (groups == 1)
	{
		do_redirs(&parser[i], redir);
		if (ft_strcmp(parser[i].command[0], "cd"))
			ft_cd(parser[i].command, parser[i].nbr_of_commands, env);
		else if (ft_strcmp(parser[i].command[0], "unset"))
			ft_unset(env, parser[i].command, parser[i].nbr_of_commands);
		else if (ft_strcmp(parser[i].command[0], "export"))
			ft_export(env, parser[i].command, parser[i].nbr_of_commands);
		else if (ft_strcmp(parser[i].command[0], "env"))
			ft_env(*env);
		else if (ft_strcmp(parser[i].command[0], "exit"))
			ft_exit(parser[i].command, parser[i].nbr_of_commands);
		else
		{
			unlinker(redir);
			return(false);
		}
		unlinker(redir);
		return(true);
	}
	return(false);
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
	if (!do_heredoc(parser, redir, groups)\
		|| single_command(parser, groups, env, redir))
		return ;
	do_exec(parser, groups, env, redir);
	close_unused_pipes(parser, groups, -1);
	while (i < groups)
	{
		waitpid(parser[i].pid, &status, 0);
		i++;
	}
	signal(SIGINT, handle_signal);
	g_exit_status = status / 256;
	unlinker(redir);
}
