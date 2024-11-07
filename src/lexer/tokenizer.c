/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:20:02 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/07 15:27:10 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void	handle_double_meta(unsigned char *input, t_lexer *lexer, unsigned int *x, unsigned int *y)
{
	if(&input[*x] == '>')
		lexer->token = APPEND_REDIRECT;
	else
		lexer->token = HEREDOC;
	lexer->str[*y] = malloc(sizeof(char) * 3);
	ft_strcpy(lexer->str[*y], &input[*x], 2);
	lexer->str[*y][2] = '\0';
	*y += 1;
	*x += 2;
}

void	handle_single_meta(unsigned char *input, t_lexer *lexer, unsigned int *x, unsigned int *y)
{
	if(&input[*x] == '\'')
		lexer->token = SINGLE_QUOTE;
	else if(&input[*x] == '\"')
		lexer->token = DOUBLE_QUOTE;
	else if(&input[*x] == '|')
		lexer->token = PIPE;
	else if(&input[*x] == '>')
		lexer->token = OUTPUT_REDIRECT;
	else if(&input[*x] == '<')
		lexer->token = INPUT_REDIRECT;
	else if(&input[*x] == '$')
		lexer->token = DOLLAR;
	lexer->str[*y] = malloc(sizeof(char) * 2);
	ft_strcpy(lexer->str[*y], &input[*x], 1);
	lexer->str[*y][1] = '\0';
	*y += 1;
	*x += 1;
}

void	handle_whitespace(unsigned char *input, t_lexer *lexer, unsigned int *x, unsigned int *y)
{
	lexer->token = SEPARATOR;
	lexer->str[*y] = malloc(sizeof(char) * 2);
	ft_strcpy(lexer->str[*y], &input[*x], 1);
	lexer->str[*y][1] = '\0';
	*y += 1;
}

void	handle_commands(unsigned char *input, t_lexer *lexer, unsigned int *x, unsigned int *y)
{
	unsigned int	i;

	i = 0;
	lexer->token = COMMAND;
	while (ft_isprint(input[*x + i]) && !ft_ismeta(input[*x + i]) && !ft_isspace(input[*x + i]))
		i++;
	lexer->str[*y] = malloc(sizeof(char) * i + 1);
	ft_strcpy(lexer->str[*y], &input[*x], i);
	lexer->str[*y][i] = '\0';
	*x += i;
	*y += 1;
}

void	tokenizer(unsigned char *input, t_lexer	*lexer)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 0;
	lexer->str = malloc(sizeof(char *) * (count_tokens(input) + 1));
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
		while (ft_isspace(input[x]))
			x++;
		if (ft_isprint(input[x]) && !ft_ismeta(input[x]) && !ft_isspace(input[x]))
			handle_commands(input, lexer, &x, &y);
	}
	lexer->str[y] = NULL;
}
