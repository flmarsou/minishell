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
	if (i < 62)
		lexer->buffer[i] = '\0';
	return (end);
}

unsigned char	*fill_string(t_lexer *lexer)
{
	unsigned char	*str;
	unsigned int	bytes_read;

	str = NULL;
	bytes_read = 0;
	lexer->length = 0;
	while (true)
	{
		bytes_read = fill_buffer(lexer);
		str = ft_realloc(str, lexer->length - bytes_read, lexer->length);
		ft_strcpy(str + (lexer->length - bytes_read), lexer->buffer, bytes_read);
		if (bytes_read != 62)
			break ;
	}
	str[lexer->length] = '\0';
	return (str);
}

int	main(void)
{
	t_lexer	lexer;

	unsigned char	*string;
	while (true)
	{
		string = fill_string(&lexer);
		printf("\nString:\n%s\n\n", string);
		free(string);
	}
	return (0);
}
