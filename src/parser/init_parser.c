/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:20:17 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/03 12:25:37 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	count_groups(t_lexer lexer)
{
	unsigned int	i;
	unsigned int	ret;

	i = 0;
	ret = 1;
	while (lexer.str[i])
	{
		if (lexer.token[i] == PIPE)
			ret++;
		i++;
	}
	return (ret);
}

void	init_parser(t_lexer lexer, t_parser *parser)
{
	unsigned int	i;

	i = 0;
	parser = malloc(sizeof(t_parser) * (count_groups(lexer) + 1));
}
