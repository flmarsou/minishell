/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:30:36 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/16 12:16:04 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	count_redirs(t_lexer lexer, unsigned int *i)
{
	unsigned int		count;

	count = 0;
	while (lexer.str[*i])
	{
		if (lexer.token[*i] == INPUT_REDIRECT
			|| lexer.token[*i] == OUTPUT_REDIRECT
			|| lexer.token[*i] == HEREDOC
			|| lexer.token[*i] == APPEND_REDIRECT)
			count++;
		if (lexer.token[*i] == PIPE)
		{
			(*i)++;
			return (count);
		}
		(*i)++;
	}
	return (count);
}

static void	alloc_redir(t_lexer *lexer, t_parser *parser, unsigned int groups)
{
	unsigned int	group;
	unsigned int	i;

	group = 0;
	i = 0;
	while (group < groups)
	{
		parser[group].nbr_of_redirs = count_redirs(*lexer, &i);
		parser[group].token = malloc(sizeof(t_tokens)
				* (parser[group].nbr_of_redirs));
		parser[group].type = malloc(sizeof(char *)
				* (parser[group].nbr_of_redirs));
		group++;
	}
}

static void	nanachi(t_lexer *lexer, unsigned int *i, unsigned int *group,
	unsigned int *index)
{
	if (lexer->token[*i] == PIPE)
	{
		*index = 0;
		(*group)++;
		(*i)++;
	}
	else
		(*i)++;
}

void	handle_redir(t_lexer *lexer, t_parser *parser, unsigned int groups)
{
	unsigned int	i;
	unsigned int	group;
	unsigned int	index;

	alloc_redir(lexer, parser, groups);
	i = 0;
	group = 0;
	index = 0;
	while (lexer->str[i])
	{
		if (lexer->token[i] == INPUT_REDIRECT
			|| lexer->token[i] == OUTPUT_REDIRECT
			|| lexer->token[i] == HEREDOC
			|| lexer->token[i] == APPEND_REDIRECT)
		{
			parser[group].token[index] = lexer->token[i];
			while (lexer->str[i] && lexer->token[i] != WORD)
				i++;
			parser[group].type[index] = ft_strdup(lexer->str[i]);
			lexer->token[i] = NA_VALUE;
			index++;
		}
		else
			nanachi(lexer, &i, &group, &index);
	}
}
