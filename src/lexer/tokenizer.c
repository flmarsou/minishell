/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:20:02 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/12 10:34:46 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_double_meta(char *input, t_lexer *lexer,
		unsigned int *x, unsigned int *y)
{
	if (input[*x] == '>')
		lexer->token[*y] = APPEND_REDIRECT;
	else
		lexer->token[*y] = HEREDOC;
	lexer->str[*y] = malloc(sizeof(char) * 3);
	lexer->str[*y][0] = input[*x];
	lexer->str[*y][1] = input[*x];
	lexer->str[*y][2] = '\0';
	*y += 1;
	*x += 2;
}

static void	handle_single_meta(char *input, t_lexer *lexer,
		unsigned int *x, unsigned int *y)
{
	if (input[*x] == '\'')
		lexer->token[*y] = SINGLE_QUOTE;
	else if (input[*x] == '\"')
		lexer->token[*y] = DOUBLE_QUOTE;
	else if (input[*x] == '|')
		lexer->token[*y] = PIPE;
	else if (input[*x] == '>')
		lexer->token[*y] = OUTPUT_REDIRECT;
	else if (input[*x] == '<')
		lexer->token[*y] = INPUT_REDIRECT;
	else if (input[*x] == '$')
		lexer->token[*y] = DOLLAR;
	lexer->str[*y] = malloc(sizeof(char) * 2);
	lexer->str[*y][0] = input[*x];
	lexer->str[*y][1] = '\0';
	*y += 1;
	*x += 1;
}

static void	handle_whitespace(char *input, t_lexer *lexer, unsigned int *x,
		unsigned int *y)
{
	unsigned int	i;

	i = 0;
	lexer->token[*y] = SEPARATOR;
	while (ft_isspace(input[*x + i]))
		i++;
	lexer->str[*y] = malloc(sizeof(char) * (i + 1));
	ft_strncpy(lexer->str[*y], &input[*x], i);
	*x += i;
	*y += 1;
}

static void	handle_commands(char *input, t_lexer *lexer, unsigned int *x,
		unsigned int *y)
{
	unsigned int	i;

	i = 0;
	lexer->token[*y] = WORD;
	while (ft_isprint(input[*x + i]) && !ft_ismeta(input[*x + i])
		&& !ft_isspace(input[*x + i]))
		i++;
	lexer->str[*y] = malloc(sizeof(char) * (i + 1));
	ft_strncpy(lexer->str[*y], &input[*x], i);
	*x += i;
	*y += 1;
}

void	tokenizer(char *input, t_lexer *lexer)
{
	unsigned int		x;
	unsigned int		y;
	const unsigned int	nbr_of_tokens = count_tokens(input);

	x = 0;
	y = 0;
	lexer->str = malloc(sizeof(char *) * (nbr_of_tokens + 1));
	lexer->token = malloc(sizeof(t_tokens) * (nbr_of_tokens));
	while (ft_isspace(input[x]))
		x++;
	while (input[x])
	{
		if ((input[x] == '>' || input[x] == '<') && input[x + 1] == input[x])
			handle_double_meta(input, lexer, &x, &y);
		else if (ft_ismeta(input[x]) && !ft_isspace(input[x]))
			handle_single_meta(input, lexer, &x, &y);
		else if (ft_isspace(input[x]))
			handle_whitespace(input, lexer, &x, &y);
		else if (ft_isprint(input[x]) && !ft_ismeta(input[x])
			&& !ft_isspace(input[x]))
			handle_commands(input, lexer, &x, &y);
		else
			x++;
	}
	lexer->str[y] = NULL;
}
