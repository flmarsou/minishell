/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:26:14 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/04 11:08:18 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_redir_error(t_lexer lexer)
{
	unsigned int	i;
	bool			quote;

	i = 0;
	quote = false;
	while (lexer.str[i])
	{
		if (!quote && (lexer.token[i] == INPUT_REDIRECT
				|| lexer.token[i] == OUTPUT_REDIRECT
				|| lexer.token[i] == HEREDOC
				|| lexer.token[i] == APPEND_REDIRECT))
			quote = true;
		else if (quote && (lexer.token[i] == INPUT_REDIRECT
				|| lexer.token[i] == OUTPUT_REDIRECT
				|| lexer.token[i] == HEREDOC
				|| lexer.token[i] == APPEND_REDIRECT
				|| lexer.token[i] == PIPE))
			break ;
		else if (quote && lexer.token[i] == WORD)
			quote = false;
		i++;
	}
	if (quote)
		return (printf(SERR"Unexpected redirection\n"), false);
	return (true);
}
