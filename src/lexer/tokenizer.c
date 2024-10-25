/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:20:02 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/24 10:32:24 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(unsigned char *input)
{
	unsigned int	i;
	unsigned int	j;
	t_lexer			**lexer;
	unsigned char	*buffer;

	i = 0;
	j = 0;
	lexer = malloc(sizeof(t_lexer *) * count_tokens(input));
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\"' || input[i] == '\'')
			while (input[i + j] != '\"' || input[i + j] != '\'')
				j++;
		while (!ft_isspace(input[i + j]))
			j++;
	}
}
