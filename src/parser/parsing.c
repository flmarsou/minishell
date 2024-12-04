/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:10:24 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/04 12:56:04 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_lexer *lexer, t_parser *parser, t_environ environ)
{
	(void)parser;
	(void)environ;
	if (!handle_quotes_error(*lexer))
		return ;
	handle_quotes(lexer);
	if (!handle_pipes_error(*lexer))
		return ;
	if (!handle_redir_error(*lexer))
		return ;
	// init_parser(*lexer, parser);
}
