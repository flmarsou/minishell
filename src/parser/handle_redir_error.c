/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:26:14 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/07 10:00:46 by anvacca          ###   ########.fr       */
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
		return (ft_putstr_fd(SERR"Unexpected redirection\n", 2), false);
	return (true);
}
