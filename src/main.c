/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/11 15:01:37 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	fill_buffer(t_lexer *lexer)
{
	unsigned int	i;
	unsigned int	end;

	i = read(STDIN, lexer->buffer, 62);
	lexer->length += i;
	end = i;
	while (i < 62)
	{
		lexer->buffer[i - 1] = '\0';
		i++;
	}
	return (end);
}

void	fill_string(t_lexer *lexer)
{
	unsigned char	*str;
	unsigned int	end;

	str = (unsigned char *)malloc(sizeof(unsigned char) * (lexer->length + 1));
	if (!str)
		exit(1);
	// TODO: Copy lexer.buffer into str.
	while (true)
	{
		// TODO: Realloc and concatenates str + lexer.buffer.
		end = fill_buffer(lexer);
		if (end != 62)
			break ;
	}
}

int	main(void)
{
	t_lexer	lexer;

	lexer.length = 0;
	while (1)
	{
		fill_string(&lexer);
	}
	return (0);
}
