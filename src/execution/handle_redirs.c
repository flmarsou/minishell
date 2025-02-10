/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:57:37 by anvacca           #+#    #+#             */
/*   Updated: 2025/02/10 09:41:25 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_name(unsigned int group)
{
	char				*ret;
	char				*itoa;

	itoa = ft_itoa(group);
	ret = ft_strjoin(".heredoc_", itoa);
	free(itoa);
	return (ret);
}

void	do_outfile(t_parser *parser, unsigned int i)
{
	int	fd;

	if (parser->token[i] == OUTPUT_REDIRECT)
	{
		fd = open(parser->type[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(ERR "Permission denied!\n", 2);
			exit(1);
		}
	}
	if (parser->token[i] == APPEND_REDIRECT)
	{
		fd = open(parser->type[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(ERR "Permission denied!\n", 2);
			exit(1);
		}
	}
	dup2(fd, STDOUT);
	close(fd);
}

void	do_in_redir(t_parser *parser, int *fd, unsigned int j)
{
	*fd = open(parser->type[j], O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd(ERR "No such file or directory\n", 2);
		exit(1);
	}
	dup2(*fd, STDIN);
	close(*fd);
}

void	do_redirs(t_parser *parser, t_redir *redir, unsigned int group)
{
	unsigned int	j;
	int				fd;
	char			*name;

	j = 0;
	if (parser->nbr_of_redirs > 0)
	{
		count_redir(parser, redir);
		while (j < parser->nbr_of_redirs)
		{
			if (parser->token[j] == HEREDOC)
			{
				name = handle_name(group);
				fd = open(name, O_RDONLY);
				free(name);
				dup2(fd, STDIN);
				close(fd);
			}
			if (parser->token[j] == INPUT_REDIRECT)
				do_in_redir(parser, &fd, j);
			if (redir->nbr_of_outfile > 0)
				do_outfile(parser, j);
			j++;
		}
	}
}
