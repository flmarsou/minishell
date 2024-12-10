/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:59:13 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/10 10:59:27 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_token(t_lexer *lexer, unsigned int y, char **buffer)
{
	lexer->token[y] = WORD;
	free(lexer->str[y]);
	lexer->str[y] = *buffer;
}
