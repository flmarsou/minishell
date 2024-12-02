/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:10:24 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/02 14:32:00 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	*lstnew_parser(void)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		ft_perror(1);
	new->group = NULL;
	new->next = NULL;
	return (new);
}

static t_parser	*init_list(t_parser *parser, t_lexer *lexer)
{
	t_parser		*head;
	unsigned int	pipe;
	unsigned int	i;

	i = 0;
	pipe = 1;
	while (lexer->str[i])
	{
		if (lexer->token[i] == PIPE)
			pipe++;
		i++;
	}
	parser = lstnew_parser();
	head = parser;
	while (pipe - 1)
	{
		parser->next = lstnew_parser();
		parser = parser->next;
		pipe--;
	}
	return (head);
}

static unsigned int count_commands(t_lexer *lexer)
{
	unsigned int	commands;
	unsigned int	i;

	i = 0;
	commands = 0;
	while (lexer->str[i])
	{
		if (lexer->str[i] && lexer->token[i] == COMMAND)
			commands++;
		while (lexer->str[i] && lexer->token[i] == COMMAND)
			i++;
		i++;
	}
	return (commands);
}

void	parsing(t_lexer *lexer, t_parser *parser, t_environ environ)
{
	unsigned int	word_count;

	handle_quotes_error(*lexer);
	handle_quotes(lexer);
	handle_dollars(lexer, environ);
	word_count = count_commands(lexer);
	printf("%u\n", word_count);
	fflush(stdout);
	parser = init_list(parser, lexer);
}
