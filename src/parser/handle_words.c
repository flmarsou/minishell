/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:55:53 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/13 13:27:59 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	edit_lexer(t_lexer *lexer, unsigned int y, unsigned int length,
	unsigned int nbr_of_token)
{
	char			*buffer;
	unsigned int	i;
	unsigned int	x;

	buffer = malloc(sizeof(char) * (length + 1));
	i = 0;
	while (nbr_of_token)
	{
		x = 0;
		if (lexer->token[y] == WORD)
		{
			while (lexer->str[y][x])
			{
				buffer[i] = lexer->str[y][x];
				i++;
				x++;
			}
			lexer->token[y] = NA_VALUE;
		}
		y++;
		nbr_of_token--;
	}
	buffer[i] = '\0';
	realloc_token(lexer, y - 1, &buffer);
}

static void	count_words(t_lexer lexer, unsigned int i,
	unsigned int *length, unsigned int *nbr_of_token)
{
	while (lexer.str[i]
		&& (lexer.token[i] == WORD || lexer.token[i] == NA_VALUE))
	{
		if (lexer.token[i] == WORD)
			*length += ft_strlen(lexer.str[i]);
		(*nbr_of_token)++;
		i++;
	}
}

static void	union_words(t_lexer *lexer)
{
	unsigned int	i;
	unsigned int	length;
	unsigned int	nbr_of_token;

	i = 0;
	while (lexer->str[i])
	{
		length = 0;
		nbr_of_token = 0;
		if (lexer->token[i] == WORD)
		{
			count_words(*lexer, i, &length, &nbr_of_token);
			if (nbr_of_token > 1)
				edit_lexer(lexer, i, length, nbr_of_token);
			i += nbr_of_token;
		}
		else
			i++;
	}
}

static void	count_quoted_words(t_lexer lexer, unsigned int i,
	unsigned int *length, unsigned int *nbr_of_token)
{
	while (lexer.str[i] && lexer.token[i] == WORD)
	{
		*length += ft_strlen(lexer.str[i]);
		(*nbr_of_token)++;
		i++;
	}
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
			lexer->str[i][0] = '\a';
			lexer->token[i++] = NA_VALUE;
			count_quoted_words(*lexer, i, &length, &nbr_of_token);
			edit_lexer(lexer, i, length, nbr_of_token);
			i += nbr_of_token;
			lexer->str[i][0] = '\a';
			lexer->token[i++] = NA_VALUE;
		}
		else
			i++;
	}
	union_words(lexer);
}
