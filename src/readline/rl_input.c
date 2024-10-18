/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:49:16 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/18 15:47:21 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	enable_raw_mode(struct termios *orig_termios)
{
	struct termios	raw;

	tcgetattr(STDIN, &raw);
	*orig_termios = raw;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN, TCSAFLUSH, &raw);
}

static void	disable_raw_mode(struct termios *orig_termios)
{
	tcsetattr(STDIN, TCSAFLUSH, orig_termios);
}

void	rl_input(t_lexer *lexer)
{
	struct termios	orig_termios;
	unsigned char	character;
	signed int		byte;
	unsigned char	seq[2];

	enable_raw_mode(&orig_termios);
	while (true)
	{
		seq[0] = '\0';
		seq[1] = '\0';
		lexer->length = 0;
		lexer->buffer = NULL;
		write(STDOUT, "\e[34m➜  \e[0m", 14);
		while (true)
		{
			byte = read(STDIN, &character, 1);
			if (character == ENTER)	
				break ;
			if (character == '\e')
			{
				read(STDIN, &seq, 2);
				if (seq[0] == '[')
				{
					if (seq[1] == 'A')
						printf("Arrow Key Up");
					else if (seq[1] == 'B')
						printf("Arrow Key Down");
					else if (seq[1] == 'C')
						printf("Arrow Key Right");
					else if (seq[1] == 'D')
						printf("Arrow Key Left");
					break ;
				}
			}
			write(STDOUT, &character, 1);
			lexer->buffer = ft_realloc(lexer->buffer, lexer->length, lexer->length + 2);
			lexer->buffer[lexer->length] = character;
			lexer->buffer[++lexer->length] = '\0';
		}
		write(STDOUT, "\n", 1);
		printf("%s | %u\n\n", lexer->buffer, lexer->length);
		if (lexer->buffer)
			free(lexer->buffer);
	}
	disable_raw_mode(&orig_termios);
}
