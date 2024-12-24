/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:53:50 by andi              #+#    #+#             */
/*   Updated: 2024/12/24 13:06:30 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	exec_builtin(char **command, t_environ **environ)
// {
// 	unsigned int	i;
// 	unsigned int	builtin;

// 	i = 1;
// 	if (ft_strcmp(command[0], "cd") == 0)
// 		ft_cd(command, &builtin);
// 	else if (ft_strcmp(command[0], "echo") == 0)
// 		ft_echo(command, &builtin);
// 	else if (ft_strcmp(command[0], "pwd") == 0)
// 		ft_pwd(&builtin);
// 	else if (ft_strcmp(command[0], "unset") == 0)
// 		while (command[i])
// 			ft_unset(environ, command[i++], &builtin);
// 	else if (ft_strcmp(command[0], "export") == 0)
// 		while (command[i])
// 			ft_export(environ, command[i++], &builtin);
// 	else if (ft_strcmp(command[0], "env") == 0)
// 		ft_env(*environ, &builtin);
// 	else if (ft_strcmp(command[0], "exit") == 0)
// 		exit(0); // TODO: ft_exit
// 	if (builtin == 1)
// 		return (true);
// 	return (false);
// }

static void	count_redirs(t_parser *parser, t_redir *redir, unsigned int groups)
{
	unsigned int	i;
	unsigned int	group;

	group = 0;
	redir->nbr_of_outfile = 0;
	redir->nbr_of_infile = 0;
	while (group < groups)
	{
		i = 0;
		while (i < parser[group].nbr_of_redirs)
		{
			if (parser[group].token[i] == OUTPUT_REDIRECT
				|| parser[group].token[i] == APPEND_REDIRECT)
				redir->nbr_of_outfile++;
			if (parser[group].token[i] == INPUT_REDIRECT
				|| parser[group].token[i] == HEREDOC)
				redir->nbr_of_infile++;
			i++;
		}
		group++;
	}
}

static void	handle_outfile(t_parser *parser, t_redir *redir,
		unsigned int groups)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	j = 0;
	k = 0;
	redir->outfile = malloc(sizeof(int) * redir->nbr_of_outfile);
	while (i < redir->nbr_of_outfile)
	{
		if (parser[j].token[i] == OUTPUT_REDIRECT)
		{
			redir->outfile[k] = open(parser[j].type[i],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			k++;
		}
		if (parser[j].token[i] == APPEND_REDIRECT)
		{
			redir->outfile[k] = open(parser[j].type[i],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			k++;
		}
		i++;
	}
}

static void	handle_infile(t_parser *parser, t_redir *redir,
		unsigned int groups)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	j = 0;
	k = 0;
	redir->infile = malloc(sizeof(int) * redir->nbr_of_infile);
	while (i < redir->nbr_of_infile)
	{
		if (parser[j].token[i] == HEREDOC)
		{
			redir->infile[k] = open();
			k++;
		}
		i++;
	}
}

void	handle_fd(t_parser *parser, unsigned int groups, t_environ *environ,
		t_redir *redir)
{
	count_redirs(parser, redir, groups);
	handle_infile(parser, groups, redir);
	// handle_outfile(parser, groups, redir);
}
