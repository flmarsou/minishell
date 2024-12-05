/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:56:41 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/05 10:47:40 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_input(t_lexer lexer, bool *found_pipe)
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
			*found_pipe = true;
		}
		else if (lexer.token[i] == WORD)
		{
			found_word = true;
			*found_pipe = false;
		}
		i++;
	}
	return (true);
}

bool	handle_pipes_error(t_lexer lexer)
{
	bool	found_pipe;

	found_pipe = false;
	if (lexer.token[0] == PIPE)
		return (ft_strerror("Syntax error, unexpected `|`"), false);
	if (!check_input(lexer, &found_pipe))
		return (ft_strerror("Syntax error, unexpected `|`"), false);
	if (found_pipe)
		return (ft_strerror("Syntax error, unexpected `|`"), false);
	return (true);
}
