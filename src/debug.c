/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:03:28 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/09 14:11:29 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer(t_lexer lexer)
{
	const char		*tokens[] = {
	[SEPARATOR] = "Separator", [WORD] = "Word", [SINGLE_QUOTE] = "Single Quote",
	[DOUBLE_QUOTE] = "Double Quote", [PIPE] = "Pipe",
	[INPUT_REDIRECT] = "Input Redirect", [OUTPUT_REDIRECT] = "Output Redirect",
	[HEREDOC] = "Heredoc", [APPEND_REDIRECT] = "Append Redirect",
	[DOLLAR] = "Dollar", [NA_VALUE] = "N/A"
	};
	unsigned int	i;

	i = 0;
	if (lexer.str[i])
	{
		fprintf(stderr, ORANGE"========== L E X E R ==========\n"RESET_COLOR);
		while (lexer.str[i])
		{
			fprintf(stderr, "String: \"\e[32m%s\e[0m\" Token: \e[32m%s\e[0m\n",
				lexer.str[i], tokens[lexer.token[i]]);
			i++;
		}
	}
}
