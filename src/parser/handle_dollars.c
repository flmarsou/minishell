/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:13:08 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/09 14:11:12 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_in_env(char *var, t_environ environ)
{
	unsigned int	len;

	len = ft_strlen(var);
	while (environ.next)
	{
		if (ft_strncmp(environ.var, var, ft_strlen(var))
			&& environ.var[len] == '=')
			return (environ.var + ft_strlen(var) + 1);
		environ = *environ.next;
	}
	return (NULL);
}

void	found_var(t_lexer *lexer, unsigned int i, char *var)
{
	lexer->str[i] = malloc(sizeof(char) * (ft_strlen(var) + 1));
	ft_strcpy(lexer->str[i], var);
}

void	no_var(t_lexer *lexer, unsigned int i)
{
	lexer->str[i] = malloc(sizeof(char) * 2);
	lexer->str[i][0] = '\a';
	lexer->str[i][1] = '\0';
	lexer->token[i] = NA_VALUE;
}

void	handle_dollars(t_lexer *lexer, t_environ environ)
{
	unsigned int	i;
	char			*var;

	i = 0;
	while (lexer->str[i])
	{
		if (lexer->token[i] == DOLLAR && lexer->token[i + 1] == WORD)
		{
			lexer->str[i][0] = '\a';
			lexer->token[i] = NA_VALUE;
			i++;
			var = find_in_env(lexer->str[i], environ);
			free(lexer->str[i]);
			if (var)
				found_var(lexer, i, var);
			else
				no_var(lexer, i);
		}
		i++;
	}
}
