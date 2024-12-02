/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:10:24 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/02 14:20:38 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_lexer *lexer, t_parser *parser, t_environ environ)
{
	handle_quotes_error(*lexer);
	handle_quotes(lexer);
	handle_dollars(lexer, environ);
}
