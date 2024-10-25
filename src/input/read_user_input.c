/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:49:16 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/25 12:27:45 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle Ctrl C and Ctrl D
static bool	process_control_characters(t_input *input, unsigned char character)
{
	if (input->buffer)
		free(input->buffer);
	input->len = 0;
	input->buffer = NULL;
	if (character == CTRL_C)
		return (true);
	else if (character == CTRL_D)
	{
		write(1, "Exiting...\n", 11);
		return (false);
	}
	return (false);
}

// Handle Arrow Keys and Delete
static void	process_escape_sequence(t_input *input)
{
	unsigned char	sequence[16];
	signed int		bytes;

	bytes = read(STDIN, &sequence, 16);
	if (!bytes)
		return ;
	if (sequence[0] == '[')
	{
		if (sequence[1] == 'C' && input->cursor_pos < input->len)
		{
			write(STDOUT, "\e[C", 3);
			input->cursor_pos++;
		}
		else if (sequence[1] == 'D' && input->cursor_pos > 0)
		{
			write(STDOUT, "\e[D", 3);
			input->cursor_pos--;
		}
		else if (sequence[1] == '3' && sequence[2] && sequence[2] == '~')
			handle_delete(input);
	}
}

// Checks what hey has been pressed in the STDIN.
static bool	process_input(t_input *input)
{
	unsigned char	character;
	signed int		byte;

	while (true)
	{
		byte = read(STDIN, &character, 1);
		if (!byte)
			return (false);
		if (character == ENTER)
			return (true);
		if (character == '\e')
			process_escape_sequence(input);
		else if (character == CTRL_C || character == CTRL_D)
			return (process_control_characters(input, character));
		else if (character == BACKSPACE)
			handle_backspace(input);
		else if (ft_isprint(character))
			handle_input(input, character);
	}
	return (true);
}

// Reads and stores STDIN into a dynamically allocated buffer.
void	read_user_input(t_input *input)
{
	input->buffer = NULL;
	input->len = 0;
	input->cursor_pos = 0;
	write(STDOUT, ORANGE "➜  " RESET_COLOR, 14);
	if (process_input(input) == false)
	{
		if (input->buffer)
			free(input->buffer);
		exit(1);
	}
	if (input->len == 0)
	{
		free(input->buffer);
		input->buffer = NULL;
	}
	write(STDOUT, "\n", 1);
}
