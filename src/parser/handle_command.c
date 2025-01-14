/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:46:15 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/06 14:58:29 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	count_commands(t_lexer lexer, bool reset)
{
	static unsigned int	i = 0;
	unsigned int		count;

	count = 0;
	if (reset)
	{
		i = 0;
		return (0);
	}
	while (lexer.str[i])
	{
		if (lexer.token[i] == WORD)
			count++;
		if (lexer.token[i] == PIPE)
		{
			i++;
			return (count);
		}
		i++;
	}
	return (count);
}

static void	alloc_commands(t_lexer *lexer, t_parser *parser,
	unsigned int groups)
{
	unsigned int	i;

	i = 0;
	while (i < groups)
	{
		parser[i].nbr_of_commands = count_commands(*lexer, false);
		parser[i].command = malloc(sizeof(char *)
				* (parser[i].nbr_of_commands));
		i++;
	}
	count_commands(*lexer, true);
}

static void	found_command(t_lexer *lexer, t_parser *parser, unsigned int *i,
	bool reset)
{
	static unsigned int	index = 0;

	if (reset)
	{
		index = 0;
		return ;
	}
	while (lexer->str[*i] && lexer->token[*i] != WORD)
		(*i)++;
	parser->command[index] = ft_strdup(lexer->str[*i]);
	index++;
}

void	handle_command(t_lexer *lexer, t_parser *parser, unsigned int groups)
{
	unsigned int	i;
	unsigned int	group;

	alloc_commands(lexer, parser, groups);
	i = 0;
	group = 0;
	while (lexer->str[i])
	{
		if (lexer->token[i] == PIPE)
		{
			group++;
			found_command(lexer, &parser[group], &i, true);
		}
		else if (lexer->token[i] == WORD)
			found_command(lexer, &parser[group], &i, false);
		i++;
	}
	found_command(lexer, &parser[group], &i, true);
}
