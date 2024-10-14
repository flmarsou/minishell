/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/14 09:34:34 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	enable_raw_mode(struct termios *orig_termios)
{
	struct termios	raw;

	tcgetattr(STDIN, &raw);
	*orig_termios = raw;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN, TCSAFLUSH, &raw);
}

void	disable_raw_mode(struct termios *orig_termios)
{
	tcsetattr(STDIN, TCSAFLUSH, orig_termios);
}

int	main(void)
{
	struct termios	orig_termios;
	t_lexer			lexer;
	unsigned char	character;
	char			byte;

	enable_raw_mode(&orig_termios);
	while (true)
	{
		lexer.length = 0;
		lexer.buffer = NULL;
		write(STDOUT, "-> ", 3);
		while (true)
		{
			byte = read(STDIN, &character, 1);
			if (!byte || character == CTRL_D)
			{
				write(STDOUT, "\n", 1);
				disable_raw_mode(&orig_termios);
				exit(0);
			}
			if (character == ENTER)
				break ;
			write(STDOUT, &character, 1);
			lexer.buffer = ft_realloc(lexer.buffer, lexer.length, lexer.length + 2);
			lexer.buffer[lexer.length] = character;
			lexer.length += byte;
			lexer.buffer[lexer.length] = '\0';
		}
		write(STDOUT, "\n", 1);
		if (lexer.buffer)
			free(lexer.buffer);
	}
	disable_raw_mode(&orig_termios);
	return (0);
}
