/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:55:45 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/04 09:48:39 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_quotes_error(t_lexer lexer)
{
	unsigned int	i;
	unsigned int	quote;

	i = 0;
	quote = 42;
	while (lexer.str[i])
	{
		if (quote == 42 && (lexer.token[i] == SINGLE_QUOTE
				|| lexer.token[i] == DOUBLE_QUOTE))
			quote = lexer.token[i];
		else if (quote != 42 && lexer.token[i] == quote)
			quote = 42;
		i++;
	}
	if (quote == SINGLE_QUOTE)
		return (printf(ERR"Syntax error, unexpected `'`\n"), false);
	else if (quote == DOUBLE_QUOTE)
		return (printf(ERR"Syntax error, unexpected `\"`\n"), false);
	return (true);
}
