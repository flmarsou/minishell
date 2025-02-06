/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:00:36 by anvacca           #+#    #+#             */
/*   Updated: 2025/02/06 15:38:57 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_redir(t_parser *parser, t_redir *redir)
{
	unsigned int	i;

	redir->nbr_of_outfile = 0;
	redir->nbr_of_infile = 0;
	i = 0;
	while (i < parser->nbr_of_redirs)
	{
		if (parser->token[i] == OUTPUT_REDIRECT
			|| parser->token[i] == APPEND_REDIRECT)
			redir->nbr_of_outfile++;
		if (parser->token[i] == INPUT_REDIRECT || parser->token[i] == HEREDOC)
			redir->nbr_of_infile++;
		i++;
	}
}

static char	*heredoc_name(unsigned int i)
{
	char	*ret;
	char	*itoa;

	itoa = ft_itoa(i++);
	ret = ft_strjoin(".heredoc_", itoa);
	free(itoa);
	return (ret);
}

void	unlinker(t_redir *redir)
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

bool	do_heredoc(t_parser *parser, t_redir *redir, unsigned int groups,
			char **env)
{
	unsigned int	j;
	unsigned int	i;
	unsigned int	count;
	bool			leave;

	j = -1;
	i = -1;
	leave = true;
	count = 1;
	while (++i < groups)
	{
		count_redir(&parser[i], redir);
		while (++j < redir->nbr_of_infile)
		{
			if (parser[i].token[j] == HEREDOC)
			{
				signal(SIGINT, SIG_IGN);
				heredoc(parser[i].type[j], &leave, count, env);
				count++;
				if (leave == false)
					return (leave);
			}
		}
	}
	return (leave);
}
