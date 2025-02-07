/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:55:45 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/07 10:00:38 by anvacca          ###   ########.fr       */
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
		return (ft_putstr_fd(SERR"Unexpected `'`\n", 2), false);
	else if (quote == DOUBLE_QUOTE)
		return (ft_putstr_fd(SERR"Unexpected `\"`\n", 2), false);
	return (true);
}
