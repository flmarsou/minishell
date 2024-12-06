/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:10:24 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/06 15:11:11 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_lexer *lexer, t_parser *parser, t_environ environ)
{
	(void)parser;
	if (!handle_quotes_error(*lexer))
		return ;
	handle_quotes(lexer);
	if (!handle_pipes_error(*lexer))
		return ;
	if (!handle_redir_error(*lexer))
		return ;
	handle_dollars(lexer, environ);
	print_lexer(*lexer);
}
