/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:10:24 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/25 15:29:10 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_pipes(t_lexer lexer, t_parser *parser)
{
	unsigned int	i;
	bool			found_word;
	bool			found_pipe;

	i = 0;
	found_pipe = false;
	parser->groups = 0;
	if (lexer.token[0] == PIPE)
	{
		ft_strerror("Can't start with a pipe!");
		return (false);
	}
	while (lexer.str[i])
	{
		found_word = false;
		if (lexer.token[i] == PIPE)
		{
			if (found_pipe)
			{
				ft_strerror("Empty or Multiple pipes!");
				return (false);
			}
			parser->groups++;
			found_pipe = true;
		}
		else if (lexer.token[i] == COMMAND)
		{
			found_word = true;
			found_pipe = false;
		}
		i++;
	}
	if (found_pipe)
	{
		ft_strerror("Can't end with a pipe!");
		return (false);
	}
	return (true);
}

void	parsing(t_lexer lexer, t_parser *parser)
{
	if (!handle_pipes(lexer, parser))
		return ;
}
