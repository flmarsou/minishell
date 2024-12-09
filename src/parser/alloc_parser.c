/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:20:17 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/09 11:47:36 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	count_groups(t_lexer lexer)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 1;
	while (lexer.str[i])
	{
		if (lexer.token[i] == PIPE)
			count++;
		i++;
	}
	return (count);
}

void	alloc_parser(t_lexer lexer, t_parser *parser)
{
	unsigned int	groups;

	groups = count_groups(lexer);
	parser = malloc(sizeof(parser) * (groups));
}
