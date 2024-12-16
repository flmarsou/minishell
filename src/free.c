/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:53:24 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/16 13:00:47 by flmarsou         ###   ########.fr       */
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

void	free_parser(t_parser *parser, unsigned int groups)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < groups)
	{
		j = 0;
		while (j < parser[i].nbr_of_redirs)
			free(parser[i].type[j++]);
		j = 0;
		while (j < parser[i].nbr_of_commands)
			free(parser[i].command[j++]);
		free(parser[i].token);
		free(parser[i].type);
		free(parser[i].command);
		i++;
	}
	free(parser);
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
