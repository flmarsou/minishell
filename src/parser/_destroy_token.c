/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _destroy_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:57:47 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/11 13:21:39 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_token(t_lexer *lexer, unsigned int y)
{
	unsigned int	i;

	i = 1;
	lexer->token[y] = NA_VALUE;
	lexer->str[y][0] = '\a';
	while (lexer->str[y][i])
	{
		lexer->str[y][i] = '\0';
		i++;
	}
}
