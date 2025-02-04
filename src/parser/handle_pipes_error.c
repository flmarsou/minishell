/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:56:41 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/04 09:48:22 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_pipes_error(t_lexer lexer)
{
	unsigned int	i;
	bool			found_pipe;

	i = 0;
	found_pipe = false;
	while (lexer.str[i])
	{
		if (lexer.token[i] == PIPE)
		{
			if (found_pipe)
				return (printf(ERR"Syntax error, unexpected `|`\n"), false);
			found_pipe = true;
		}
		else if (lexer.token[i] == WORD)
			found_pipe = false;
		i++;
	}
	if (found_pipe)
		return (printf(ERR"Syntax error, unexpected `|`\n"), false);
	return (true);
}
