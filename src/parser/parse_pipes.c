/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:54:41 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/26 13:05:36 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	loop(t_lexer lexer, t_parser *parser, bool *found_pipe)
{
	unsigned int	i;
	bool			found_word;

	i = 0;
	while (lexer.str[i])
	{
		found_word = false;
		if (lexer.token[i] == PIPE)
		{
			if (*found_pipe)
				return (false);
			parser->groups++;
			*found_pipe = true;
		}
		else if (lexer.token[i] == COMMAND)
		{
			found_word = true;
			*found_pipe = false;
		}
		i++;
	}
	return (true);
}

bool	handle_pipes_error(t_lexer lexer, t_parser *parser)
{
	bool			found_pipe;

	found_pipe = false;
	parser->groups = 0;
	if (lexer.token[0] == PIPE)
		return (ft_strerror("Can't start with a pipe!"), false);
	if (!loop(lexer, parser, &found_pipe))
		return (ft_strerror("Empty or Multiple pipes!"), false);
	if (found_pipe)
		return (ft_strerror("Can't end with a pipe!"), false);
	return (true);
}
