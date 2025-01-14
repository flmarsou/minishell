/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:03:28 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/16 13:05:33 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define LEXER_BANNER	"==================== L E X E R ====================\n"
#define PARSER_BANNER	"=================== P A R S E R ===================\n"
#define PRINT_N_COMMAND	"Group[%u] - No Command Found!\n"
#define PRINT_COMMAND	"Group[%u] - Command[%u]: %s\n"
#define PRINT_N_REDIR	"Group[%u] - No Redir Found!\n"
#define PRINT_REDIR		"Group[%u] - Redir[%u] (%s): %s\n"

static void	print_parser_command(t_parser parser, unsigned int i)
{
	unsigned int	j;

	if (parser.nbr_of_commands == 0)
		fprintf(stderr, PRINT_N_COMMAND, i);
	else
	{
		j = 0;
		while (j < parser.nbr_of_commands)
		{
			fprintf(stderr, PRINT_COMMAND, i, j, parser.command[j]);
			j++;
		}
	}
}

static void	print_parser_redir(t_parser parser, unsigned int i)
{
	unsigned int	j;
	const char		*tokens[] = {
	[INPUT_REDIRECT] = "Input Redirect", [OUTPUT_REDIRECT] = "Output Redirect",
	[HEREDOC] = "Heredoc", [APPEND_REDIRECT] = "Append Redirect"
	};

	if (parser.nbr_of_redirs == 0)
		fprintf(stderr, PRINT_N_REDIR, i);
	else
	{
		j = 0;
		while (j < parser.nbr_of_redirs)
		{
			fprintf(stderr, PRINT_REDIR, i, j,
				tokens[parser.token[j]], parser.type[j]);
			j++;
		}
	}
}

void	print_parser(t_parser *parser, unsigned int groups)
{
	unsigned int	i;

	i = 0;
	fprintf(stderr, PARSER_BANNER);
	while (i < groups)
	{
		print_parser_command(parser[i], i);
		fprintf(stderr, "\n");
		print_parser_redir(parser[i], i);
		i++;
		if (i < groups)
			fprintf(stderr, "\n\n");
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
