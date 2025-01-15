/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:39:22 by anvacca           #+#    #+#             */
/*   Updated: 2025/01/15 15:12:05 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(char **command, t_environ **environ,
		unsigned int nbr_of_cmd)
{
	unsigned int	i;

	i = 1;
	// if (ft_strcmp(command[0], "cd") == 0)
	// 	ft_cd(command[i]);
	if (ft_strcmp(command[0], "echo"))
		ft_echo(command, nbr_of_cmd);
	else if (ft_strcmp(command[0], "pwd"))
		ft_pwd();
	else if (ft_strcmp(command[0], "unset"))
	{
		while (i < nbr_of_cmd)
			ft_unset(environ, command[i++]);
	}
	else if (ft_strcmp(command[0], "export"))
		ft_export(environ, command, nbr_of_cmd);
	else if (ft_strcmp(command[0], "env"))
		ft_env(*environ);
	// else if (ft_strcmp(command[0], "exit"))
	// 	exit(0); // TODO: ft_exit
	else
		// execve
		exit(0);
	return ;
}

void	do_outfile(t_parser *parser, t_redir *redir, t_environ **environ)
{
	unsigned int	i;
	int				fd_out;

	fd_out = dup(STDOUT_FILENO);
	i = 0;
	while (i < redir->nbr_of_outfile)
	{
		dup2(redir->outfile[i], STDOUT_FILENO);
		exec_builtin(parser->command, environ, parser->nbr_of_commands);
		close(redir->outfile[i]);
		i++;
	}
	dup2(fd_out, STDOUT_FILENO);
}

void	do_infile(t_parser *parser, t_redir *redir, t_environ **environ)
{
	unsigned int	j;
	int				fd_in;

	j = 0;
	fd_in = dup(STDIN);
	while (j < redir->nbr_of_infile)
	{
		dup2(redir->infile[j], STDIN);
		if (redir->nbr_of_outfile > 0)
			do_outfile(parser, redir, environ);
		else
			exec_builtin(parser->command, environ, parser->nbr_of_commands);
		close(redir->infile[j]);
		j++;
	}
	dup2(fd_in, STDIN);
}

void	do_redir(t_parser *parser, t_redir *redir, t_environ **environ)
{
	if (redir->nbr_of_infile > 0)
		do_infile(parser, redir, environ);
	else if (redir->nbr_of_outfile > 0)
		do_outfile(parser, redir, environ);
}

void	exec(t_parser *parser, unsigned int groups, t_environ **environ,
		t_redir *redir)
{
	unsigned int	i;
	pid_t			pid;

	i = 0;
	redir->nbr_of_outfile = 0;
	redir->nbr_of_infile = 0;
	while (i < groups)
	{
		pid = fork();
		if (pid = 0)
		{
			if (parser[i].nbr_of_redirs > 0)
				handle_fd(parser, i, redir);
			do_redir(&parser[i], redir, environ);
		}
	}
}
