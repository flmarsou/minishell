/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:30:36 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/11 13:44:43 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	count_redirs(t_lexer lexer, bool reset)
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
		if (lexer.token[i] == INPUT_REDIRECT
			|| lexer.token[i] == OUTPUT_REDIRECT
			|| lexer.token[i] == HEREDOC
			|| lexer.token[i] == APPEND_REDIRECT)
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

void	found_redir(t_lexer *lexer, t_parser *parser, unsigned int *i, bool reset)
{
	static unsigned int	index = 0;

	if (reset)
	{
		index = 0;
		return ;
	}
	parser->redir.token[index] = lexer->token[*i];
	destroy_token(lexer, *i);
	while (lexer->str[*i] && lexer->token[*i] != WORD)
		(*i)++;
	parser->redir.type[index] = ft_strdup(lexer->str[*i]);
	destroy_token(lexer, *i);
	index++;
}

// void	print_parser(t_parser parser)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (i < parser.redir.nbr_of_redirs)
// 	{
// 		fprintf(stderr, "Redir.token[i] = %d\n", parser.redir.token[i]);
// 		fprintf(stderr, "Redir.type[i] = %s\n", parser.redir.type[i]);
// 		i++;
// 	}
	
// }

void	handle_redir(t_lexer *lexer, t_parser *parser, unsigned int groups)
{
	unsigned int	i;
	unsigned int	group;

	i = 0;
	while (i < groups)
	{
		parser[i].redir.nbr_of_redirs = count_redirs(*lexer, false);
		parser[i].redir.token = malloc(sizeof(t_tokens) * (parser[i].redir.nbr_of_redirs));
		parser[i].redir.type = malloc(sizeof(char *) * (parser[i].redir.nbr_of_redirs + 1));
		parser[i].redir.type[parser[i].redir.nbr_of_redirs] = NULL;
		i++;
	}
	count_redirs(*lexer, true);
	i = 0;
	group = 0;
	while(lexer->str[i])
	{
		if (lexer->token[i] == PIPE)
		{
			group++;
			found_redir(lexer, &parser[group], &i, true);
		}
		if (lexer->token[i] == INPUT_REDIRECT
				|| lexer->token[i] == OUTPUT_REDIRECT
				|| lexer->token[i] == HEREDOC
				|| lexer->token[i] == APPEND_REDIRECT)
			found_redir(lexer, &parser[group], &i, false);
		else
			i++;
	}
}
