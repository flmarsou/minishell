/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:10:24 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/11 10:23:22 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_lexer lexer, t_parser *parser)
{
	unsigned int	i;

	parser = malloc(sizeof(t_parser) * 1000);
	i = 0;
	while (lexer.str[i])
	{
		i++;
	}
}
