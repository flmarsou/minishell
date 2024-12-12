/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:53:24 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/12 09:44:00 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_environ *environ)
{
	t_environ	*temp;

	while (environ)
	{
		temp = environ->next;
		free(environ);
		environ = temp;
	}
}

void	free_parser(t_parser *parser)
{
	
}

void	free_lexer(t_lexer *lexer)
{
	unsigned int	i;

	i = 0;
	if (lexer->str)
	{
		while (lexer->str[i])
		{
			free(lexer->str[i]);
			i++;
		}
		free(lexer->str);
		lexer->str = NULL;
		free(lexer->token);
		lexer->token = NULL;
	}
}
