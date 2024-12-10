/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:18:57 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/10 11:38:27 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Turns all tokens encapsulated in double quotes to `COMMAND`.
static void	single_quote(t_lexer *lexer, unsigned int *i)
{
	(*i)++;
	while (lexer->str[*i] && lexer->token[*i] != SINGLE_QUOTE)
	{
		lexer->token[*i] = WORD;
		(*i)++;
	}
	(*i)++;
}

// Turns all tokens encapsulated in double quotes to `COMMAND` except `DOLLAR`.
static void	double_quote(t_lexer *lexer, unsigned int *i)
{
	(*i)++;
	while (lexer->str[*i] && lexer->token[*i] != DOUBLE_QUOTE)
	{
		if (lexer->token[*i] != DOLLAR)
			lexer->token[*i] = WORD;
		(*i)++;
	}
	(*i)++;
}

void	handle_quotes(t_lexer *lexer)
{
	unsigned int	i;

	i = 0;
	while (lexer->str[i])
	{
		if (lexer->token[i] == SINGLE_QUOTE)
			single_quote(lexer, &i);
		else if (lexer->token[i] == DOUBLE_QUOTE)
			double_quote(lexer, &i);
		else
			i++;
	}
}
