/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:55:53 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/09 15:58:23 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO
// Fuses all words found here until you meet a single or double quote.
// nbr_of_token -> How many tokens to iterate through
// length -> total length of all the words to use (chars)
static void	edit_lexer(t_lexer *lexer, unsigned int *i, unsigned int length,
	unsigned int nbr_of_token)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	*i += nbr_of_token;
}

static void	count_words(t_lexer lexer, unsigned int i, unsigned int *length,
	unsigned int *nbr_of_token)
{
	while (lexer.str[i] && lexer.token[i] == WORD)
	{
		*length += ft_strlen(lexer.str[i]);
		(*nbr_of_token)++;
		i++;
	}
}

static void	remove_quote(t_lexer *lexer, unsigned int *i)
{
	lexer->str[*i][0] = '\a';
	lexer->token[*i] = NA_VALUE;
	(*i)++;
}

void	handle_words(t_lexer *lexer)
{
	unsigned int	i;
	unsigned int	length;
	unsigned int	nbr_of_token;

	i = 0;
	while (lexer->str[i])
	{
		length = 0;
		nbr_of_token = 0;
		if (lexer->token[i] == SINGLE_QUOTE || lexer->token[i] == DOUBLE_QUOTE)
		{
			remove_quote(lexer, &i);
			count_words(*lexer, i, &length, &nbr_of_token);
			edit_lexer(lexer, &i, length, nbr_of_token);
			remove_quote(lexer, &i);
		}
		else
			i++;
	}
}
