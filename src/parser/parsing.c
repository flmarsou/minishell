/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:10:24 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/06 13:27:30 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	count_groups(t_lexer lexer)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 1;
	while (lexer.str[i])
	{
		if (lexer.token[i] == PIPE)
			count++;
		i++;
	}
	return (count);
}

bool	parsing(t_lexer *lexer, t_parser **parser, t_environ environ,
	unsigned int *groups)
{
	if (!handle_quotes_error(*lexer))
		return (false);
	handle_quotes(lexer);
	if (!handle_pipes_error(*lexer))
		return (false);
	handle_dollars(lexer, environ);
	if (!handle_redir_error(*lexer))
		return (false);
	handle_words(lexer);
	*groups = count_groups(*lexer);
	*parser = malloc(sizeof(t_parser) * (*groups));
	handle_redir(lexer, *parser, *groups);
	handle_command(lexer, *parser, *groups);
	return (true);
}
