/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:39:22 by anvacca           #+#    #+#             */
/*   Updated: 2025/01/06 15:19:49 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exec_builtin(char **command, t_environ **environ, unsigned int nbr_of_cmd)
{
	unsigned int	i;

	i = 1;
	// if (ft_strcmp(command[0], "cd") == 0)
	// 	ft_cd(command[i]);
	if (ft_strcmp(command[0], "echo"))
		return (ft_echo(command, nbr_of_cmd), true);
	else if (ft_strcmp(command[0], "pwd"))
		return (ft_pwd(), true);
	else if (ft_strcmp(command[0], "unset"))
	{
		while (i < nbr_of_cmd)
			ft_unset(environ, command[i++]);
		return (true);
	}
	else if (ft_strcmp(command[0], "export"))
		return (ft_export(environ, command, nbr_of_cmd), true);
	else if (ft_strcmp(command[0], "env"))
		return (ft_env(*environ), true);
	// else if (ft_strcmp(command[0], "exit"))
	// 	exit(0); // TODO: ft_exit
	return (false);
}

void	do_pipe(t_parser *parser, t_redir *redir, t_environ **environ)
{
	unsigned int	i;
	int				fd_temp;

	i = 0;
	fd_temp = STDOUT_FILENO;
	while (i < redir->nbr_of_outfile)
	{
		printf("%d\n", redir->nbr_of_outfile);
		dup2(redir->outfile[i], fd_temp);
		if (exec_builtin(parser->command, environ, parser->nbr_of_commands) == false)
			puts("execve");
		close(redir->outfile[i]);
		i++;
	}
	if (redir->nbr_of_outfile == 0)
		if (exec_builtin(parser->command, environ, parser->nbr_of_commands) == false)
			puts("execve");
}

void	exec(t_parser *parser, unsigned int groups, t_environ **environ,
		t_redir *redir)
{
	unsigned int	i;
	// int				fd1;
	
	// fd1 = dup(STDOUT_FILENO);
	i = 0;
	redir->nbr_of_outfile = 0;
	redir->nbr_of_infile = 0;
	// while (i < groups - 1)
	// {
	if (parser[i].nbr_of_redirs > 0)
		handle_fd(parser, i, redir);
	do_pipe(&parser[i], redir, environ);
	// }
}
