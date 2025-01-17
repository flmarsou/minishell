/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:39:22 by anvacca           #+#    #+#             */
/*   Updated: 2025/01/17 14:25:01 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_builtin(char **command, unsigned int nbr_of_cmd)
{
	unsigned int	i;

	i = 1;
	if (ft_strcmp(command[0], "export") && nbr_of_cmd - 1 > 0)
		return (true);
	else if (ft_strcmp(command[0], "unset") && nbr_of_cmd - 1 > 0)
		return (true);
	// else if (ft_strcmp(command[0], "cd"))
	// 	return(true);
	else if (ft_strcmp(command[0], "exit") == true)
		return (true);
	return (false);
}

void	exec_builtin(char **command, char ***env, unsigned int nbr_of_cmd)
{
	unsigned int	i;

	i = 1;
	// if (ft_strcmp(command[0], "cd"))
	// 	ft_cd(command[i]);
	if (ft_strcmp(command[0], "echo"))
		ft_echo(command, nbr_of_cmd);
	else if (ft_strcmp(command[0], "pwd"))
		ft_pwd();
	else if (ft_strcmp(command[0], "unset"))
			ft_unset(env, command, nbr_of_cmd);
	// else if (ft_strcmp(command[0], "export"))
	// 	ft_export(environ, command, nbr_of_cmd);
	else if (ft_strcmp(command[0], "env"))
		ft_env(*env);
	// else if (ft_strcmp(command[0], "exit"))
	// 	exit(0); // TODO: ft_exit
	else
		// execve
		execve("/bin/ls", command, NULL);
	return ;
}

void	do_outfile(t_parser *parser, t_redir *redir, char ***env)
{
	unsigned int	i;

	i = 0;
	while (i < redir->nbr_of_outfile)
	{
		dup2(redir->outfile[i], STDOUT_FILENO);
		close(redir->outfile[i]);
		i++;
	}
}

void	do_infile(t_parser *parser, t_redir *redir, char ***env)
{
	unsigned int	j;

	j = 0;
	while (j < redir->nbr_of_infile)
	{
		dup2(redir->infile[j], STDIN);
		if (redir->nbr_of_outfile > 0)
		{
			do_outfile(parser, redir, env);
			exec_builtin(parser->command, env, parser->nbr_of_commands);
		}
		close(redir->infile[j]);
		j++;
	}
}

void	do_exec(t_parser *parser, t_redir *redir, char ***env)
{
	if (redir->nbr_of_infile > 0)
		do_infile(parser, redir, env);
	else if (redir->nbr_of_outfile > 0)
	{
		do_outfile(parser, redir, env);
		exec_builtin(parser->command, env, parser->nbr_of_commands);
	}
}

void	exec(t_parser *parser, unsigned int groups, char ***env,
		t_redir *redir)
{
	unsigned int	i;
	pid_t			pid;
	int				fd_in;
	int				fd_out;
	int				status;

	i = 0;
	redir->nbr_of_outfile = 0;
	redir->nbr_of_infile = 0;
	fd_in = dup(STDIN);
	fd_out = dup(STDOUT);
	while (i < groups)
	{
		if (i == 0 && check_builtin(parser[i].command,
				parser[i].nbr_of_commands))
			exec_builtin(parser[i].command, env, parser[i].nbr_of_commands);
		else
		{
			pid = fork();
			if (i < groups - 1)
				pipe(parser[i].fd);
			if (pid == 0)
			{
				if (i > 0)
				{
					close(parser[i - 1].fd[1]);
					dup2(parser[i - 1].fd[0], STDIN);
				}
				close(parser[i].fd[0]);
				handle_fd(parser, i, redir);
				do_exec(&parser[i], redir, env);
				if (i < groups - 1)
					dup2(parser[i].fd[1], STDOUT);
				exec_builtin(parser[i].command, env,
					parser[i].nbr_of_commands);
				dup2(fd_in, STDIN);
				exit(0);
			}
		}
		i++;
	}
	if (pid > 0)
	{
		i = 0;
		waitpid(pid, &status, 0);
		while (i < groups - 1)
		{
			close(parser[i].fd[0]);
			close(parser[i].fd[1]);
			i++;
		}
		dup2(fd_out, STDOUT);
	}
}
