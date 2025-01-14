/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:53:50 by andi              #+#    #+#             */
/*   Updated: 2025/01/06 15:04:50 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_redirs(t_parser *parser, t_redir *redir, unsigned int group)
{
	unsigned int	i;

	redir->nbr_of_outfile = 0;
	redir->nbr_of_infile = 0;
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
}

static void	handle_outfile(t_parser *parser, t_redir *redir)
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

static void	handle_infile(t_parser *parser, t_redir *redir)
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
			redir->infile[k] = heredoc(parser[j].type[i]);
			k++;
			redir->nbr_of_infile++;
		}
		i++;
	}
}

void	handle_fd(t_parser *parser, unsigned int group, t_redir *redir)
{
	count_redirs(parser, redir, group);
	handle_infile(parser, redir);
	handle_outfile(parser, redir);
	// int fd = dup(STDOUT_FILENO);
	// dup2(redir->outfile[0], STDOUT_FILENO);
	// puts("caca");
	// dup2(redir->outfile[1], STDOUT_FILENO);
	// dup2(fd, STDOUT_FILENO);
}
