/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:55:45 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/29 10:13:31 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_quote_error(t_lexer lexer)
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
	if (quote != 42)
		return (ft_strerror("Wrong quote placement!"), false);
	return (true);
}
