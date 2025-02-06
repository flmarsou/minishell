/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:10:24 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/06 13:08:38 by flmarsou         ###   ########.fr       */
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

bool	parsing(t_lexer *lexer, t_parser **parser, char **env,
	unsigned int *groups)
{
	if (!handle_quotes_error(*lexer))
		return (lexer->exit_status = 2, false);
	handle_quotes(lexer);
	if (!handle_pipes_error(*lexer))
		return (lexer->exit_status = 2, false);
	handle_dollars(lexer, env);
	if (!handle_redir_error(*lexer))
		return (lexer->exit_status = 2, false);
	handle_words(lexer);
	*groups = count_groups(*lexer);
	*parser = malloc(sizeof(t_parser) * (*groups));
	handle_redir(lexer, *parser, *groups);
	handle_command(lexer, *parser, *groups);
	return (lexer->exit_status = 0, true);
}
