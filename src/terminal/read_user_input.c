/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:49:16 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/31 12:56:33 by flmarsou         ###   ########.fr       */
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
		write(1, "\nExiting...\n", 11);
		return (false);
	}
	return (false);
}

// && input->cursor_x < input->len
// Handle Arrow Keys and Delete
static void	process_escape_sequence(t_input *input)
{
	unsigned char	sequence[4];
	signed int		bytes;
	unsigned int	i;

	i = 0;
	bytes = read(STDIN, &sequence, 4);
	if (bytes <= 0)
		return ;
	if (sequence[0] == '[')
	{	
		if (sequence[1] == 'D' && input->cursor_x > 0)
		{
			arrow_key_left(input);
			input->cursor_x--;
		}
		else if (sequence[1] == 'C' && input->cursor_x < input->len)
		{
			arrow_key_right(input);
			input->cursor_x++;
		}
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
	input->alloc_len = 0;
	input->cursor_x = 0;
	input->term_lines = 0;
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
