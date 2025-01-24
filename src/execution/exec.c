/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:39:22 by anvacca           #+#    #+#             */
/*   Updated: 2025/01/24 13:21:30 by anvacca          ###   ########.fr       */
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
		ft_execve(command, *env);
	return ;
}

void	do_outfile(t_parser *parser, t_redir *redir, char ***env)
{
	unsigned int	i;

	i = 0;
	while (i < redir->nbr_of_outfile)
	{
		dup2(redir->outfile[i], STDOUT);
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
	printf("%d\n%d\n", redir->nbr_of_infile, redir->nbr_of_outfile);
	if (redir->nbr_of_infile > 0)
		do_infile(parser, redir, env);
	else if (redir->nbr_of_outfile > 0)
		do_outfile(parser, redir, env);
}

void	handle_signal_child(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT, "\n", 1);
		exit(0);
	}
}

void	init_pipes(t_parser *parser, unsigned int groups)
{
	unsigned int i;

	i = 0;
	while (i < groups - 1)
	{
		pipe(parser[i].fd);
		i++;
	}
}

void	close_unused_pipes(t_parser *parser, unsigned int groups, unsigned int i)
{
	unsigned int j;

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

void	exec(t_parser *parser, unsigned int groups, char ***env, t_redir *redir)
{
	unsigned int	i;
	pid_t			pid;
	int				status;

	i = 0;
	redir->nbr_of_outfile = 0;
	redir->nbr_of_infile = 0;
	init_pipes(parser, groups);
	signal(SIGINT, SIG_IGN);
	while (i < groups)
	{
		if (!handle_fd(parser, i, redir))
		{
			if (redir->nbr_of_infile > 0)
				free(redir->infile);
			if (redir->nbr_of_outfile > 0)
				free(redir->outfile);
			unlinker(redir);
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, handle_signal_child);
			do_exec(&parser[i], redir, env);
			if (groups > 1)
			{
				close_unused_pipes(parser, groups, i);
				pipes(parser, groups, i);
			}
			if (parser[i].nbr_of_commands > 0)
				exec_builtin(parser[i].command, env,
					parser[i].nbr_of_commands);
		}
		i++;
	}
	if (pid > 0)
	{
		i = 0;
		while(i < groups - 1)
		{
			close(parser[i].fd[0]);
			close(parser[i].fd[1]);
			i++;
		}
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_signal);
		g_exit_status = status / 256;
		if (redir->nbr_of_infile > 0)
			free(redir->infile);
		if (redir->nbr_of_outfile > 0)
			free(redir->outfile);
		unlinker(redir);
	}
}
