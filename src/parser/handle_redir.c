/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:30:36 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/09 15:58:28 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static unsigned int	count_redirs(t_lexer lexer, bool reset)
// {
// 	static unsigned int	i = 0;
// 	unsigned int		count;

// 	count = 0;
// 	if (reset)
// 	{
// 		i = 0;
// 		return (0);
// 	}
// 	while (lexer.str[i])
// 	{
// 		if (lexer.token[i] == INPUT_REDIRECT
// 			|| lexer.token[i] == OUTPUT_REDIRECT
// 			|| lexer.token[i] == HEREDOC
// 			|| lexer.token[i] == APPEND_REDIRECT)
// 			count++;
// 		if (lexer.token[i++] == PIPE)
// 			return (count);
// 		i++;
// 	}
// 	return (count);
// }

// void	found_redir(t_lexer *lexer, t_parser *parser, unsigned int *i,
// 	unsigned int *group)
// {
// }

// void	handle_redir(t_lexer *lexer, t_parser *parser)
// {
// 	unsigned int	i;
// 	unsigned int	group;

// 	i = 0;
// 	group = 0;
// 	while (lexer->str[i])
// 	{
// 		while (lexer->token[i] != PIPE)
// 		{
// 			if (lexer->token[i] == INPUT_REDIRECT
// 				|| lexer->token[i] == OUTPUT_REDIRECT
// 				|| lexer->token[i] == HEREDOC
// 				|| lexer->token[i] == APPEND_REDIRECT)
// 				found_redir(lexer, parser, &i, &group);
// 			group++;
// 		}
// 		i++;
// 	}
// }
