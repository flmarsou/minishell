/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_output_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andi <andi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:19:26 by andi              #+#    #+#             */
/*   Updated: 2024/12/12 19:23:04 by andi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int is_output_redir(t_parser *parser)
{
	unsigned int i;
	unsigned int count;

	i = 0;
	count = 0;
	while (parser->redir.type[i])
	{
		if(parser->redir.token[i] == OUTPUT_REDIRECT)
			count++;
		i++;
	}
	return (count);
}