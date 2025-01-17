/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:53:50 by andi              #+#    #+#             */
/*   Updated: 2025/01/17 13:30:52 by anvacca          ###   ########.fr       */
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
	unsigned int	k;

	i = 0;
	k = 0;
	redir->outfile = malloc(sizeof(int) * redir->nbr_of_outfile);
	while (i < redir->nbr_of_outfile)
	{
		if (parser->token[i] == OUTPUT_REDIRECT)
		{
			redir->outfile[k] = open(parser->type[i],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			k++;
		}
		if (parser->token[i] == APPEND_REDIRECT)
		{
			redir->outfile[k] = open(parser->type[i],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			k++;
		}
		i++;
	}
}

static void	handle_infile(t_parser *parser, t_redir *redir)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	k = 0;
	redir->infile = malloc(sizeof(int) * redir->nbr_of_infile);
	while (i < redir->nbr_of_infile)
	{
		if (parser->token[i] == HEREDOC)
		{
			redir->infile[k] = heredoc(parser->type[i]);
			k++;
		}
		if (parser->token[i] == INPUT_REDIRECT)
		{
			redir->infile[k] = open(parser->type[i], O_RDONLY);
			k++;
		}
		i++;
	}
}

void	handle_fd(t_parser *parser, unsigned int group, t_redir *redir)
{
	if (parser[group].nbr_of_redirs > 0)
	{
		count_redirs(parser, redir, group);
		handle_infile(&parser[group], redir);
		handle_outfile(&parser[group], redir);
	}
	// int fd = dup(STDOUT_FILENO);
	// dup2(redir->outfile[0], STDOUT_FILENO);
	// puts("caca");
	// dup2(redir->outfile[1], STDOUT_FILENO);
	// dup2(fd, STDOUT_FILENO);
}
