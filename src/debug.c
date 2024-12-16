/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:03:28 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/16 12:21:59 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define LEXER_BANNER	"==================== L E X E R ====================\n"
#define PARSER_BANNER	"=================== P A R S E R ===================\n"
#define PRINT_N_COMMAND	"Group[%u] - No Command Found!\n"
#define PRINT_COMMAND	"Group[%u] - Command[%u]: %s\n"
#define PRINT_N_REDIR	"Group[%u] - No Redir Found!\n"
#define PRINT_REDIR		"Group[%u] - Redir[%u]: %s\n"

void	print_parser(t_parser *parser, unsigned int groups)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	fprintf(stderr, PARSER_BANNER);
	while (i < groups)
	{
		if (parser[i].nbr_of_redirs == 0)
			fprintf(stderr, PRINT_N_REDIR, i);
		else
		{
			j = 0;
			while (j < parser[i].nbr_of_redirs)
			{
				fprintf(stderr, PRINT_REDIR, i, j, parser[i].type[j]);
				j++;
			}
		}
		fprintf(stderr, "\n");
		i++;
	}
}

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
		fprintf(stderr, LEXER_BANNER);
		while (lexer.str[i])
		{
			fprintf(stderr, "String: \"%s\" Token: %s\n",
				lexer.str[i], tokens[lexer.token[i]]);
			i++;
		}
	}
}
