/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:39:22 by anvacca           #+#    #+#             */
/*   Updated: 2025/01/23 12:29:07 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_name(unsigned int i)
{
	char			*ret;
	char			*itoa;

	itoa = ft_itoa(i++);
	ret = ft_strjoin(".heredoc_", itoa);
	free(itoa);
	return (ret);
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

bool	check_builtin(char **command, unsigned int nbr_of_cmd)
{
	unsigned int	i;

	i = 1;
	if (nbr_of_cmd < 1)
		return (false);
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
		exit(0); // TODO: ft_exit
	else
		// execve
		puts("caca");
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
			do_outfile(parser, redir, env);
		close(redir->infile[j]);
		j++;
	}
}

void	do_exec(t_parser *parser, t_redir *redir, char ***env)
{
	if (redir->nbr_of_infile > 0)
		do_infile(parser, redir, env);
	else if (redir->nbr_of_outfile > 0)
		do_outfile(parser, redir, env);
}

void	exec(t_parser *parser, unsigned int groups, char ***env, t_redir *redir)
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
	if (!handle_fd(parser, groups, redir))
	{
		if (redir->nbr_of_infile > 0)
			free(redir->infile);
		if (redir->nbr_of_outfile > 0)
			free(redir->outfile);
		unlinker(redir);
		return ;
	}
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
				do_exec(&parser[i], redir, env);
				if (i < groups - 1)
					dup2(parser[i].fd[1], STDOUT);
				if (parser[i].nbr_of_commands > 0)
					exec_builtin(parser[i].command, env,
						parser[i].nbr_of_commands);
				dup2(fd_in, STDIN);
				free_parser(parser, groups);
				free_env(env);
				exit(0);
			}
		}
		i++;
	}
	if (pid > 0)
	{
		i = 0;
		waitpid(pid, &status, 0);
		g_exit_status = status / 256;
		dup2(fd_out, STDOUT);
		if (redir->nbr_of_infile > 0)
			free(redir->infile);
		if (redir->nbr_of_outfile > 0)
			free(redir->outfile);
		unlinker(redir);
	}
}
