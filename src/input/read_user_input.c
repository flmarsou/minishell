/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:49:16 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/21 09:27:16 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	process_control_characters(t_lexer *lexer, unsigned char character)
{
	if (lexer->buffer)
		free(lexer->buffer);
	lexer->length = 0;
	lexer->buffer = NULL;
	if (character == CTRL_C)
		return (true);
	else if (character == CTRL_D)
	{
		write(1, "Exiting...\n", 11);
		return (false);
	}
	return (false);
}

static bool	process_escape_sequence(void)
{
	unsigned char	sequence[2];
	signed int		bytes;

	bytes = read(STDIN, &sequence, 2);
	if (!bytes)
		return (false);
	if (sequence[0] == '[')
	{
		if (sequence[1] == 'A')
			printf("Arrow Key Up");
		else if (sequence[1] == 'B')
			printf("Arrow Key Down");
		else if (sequence[1] == 'C')
			printf("Arrow Key Right");
		else if (sequence[1] == 'D')
			printf("Arrow Key Left");
		return (true);
	}
	return (false);
}

static bool	handle_input(t_lexer *lexer)
{
	unsigned char	character;
	signed int		byte;

	write(STDOUT, ORANGE"➜  "RESET_COLOR, 14);
	while (true)
	{
		byte = read(STDIN, &character, 1);
		if (!byte)
			return (false);
		if (character == ENTER)
			return (true);
		if (character == '\e')
			return (process_escape_sequence());
		if (character == CTRL_C || character == CTRL_D)
			return (process_control_characters(lexer, character));
		else
		{
			write(STDOUT, &character, 1);
			lexer->buffer = ft_realloc(lexer->buffer, lexer->length, lexer->length + 2);
			lexer->buffer[lexer->length] = character;
			lexer->buffer[++lexer->length] = '\0';
		}
	}
	return (true);
}

void	read_user_input(t_lexer *lexer)
{
	struct termios	orig_termios;

	enable_raw_mode(&orig_termios);
	while (true)
	{
		lexer->length = 0;
		lexer->buffer = NULL;
		if (handle_input(lexer) == false)
			break ;
		write(STDOUT, "\n", 1);
		printf("%s | %u\n\n", lexer->buffer, lexer->length);
		if (lexer->buffer)
			free(lexer->buffer);
	}
	disable_raw_mode(&orig_termios);
}
