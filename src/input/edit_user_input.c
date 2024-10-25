/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:33:07 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/25 12:27:52 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Shifts the buffer one position to the right starting at cursor_pos.
// Redraws the modified buffer in STDOUT and moves the cursor back.
void	handle_delete(t_input *input)
{
	unsigned int	move_cursor;

	if (input->cursor_pos >= input->len)
		return ;
	ft_strmove(&input->buffer[input->cursor_pos],
		&input->buffer[input->cursor_pos + 1], input->len - input->cursor_pos
		- 1);
	input->buffer = ft_realloc(input->buffer, input->len, input->len - 1);
	input->buffer[--input->len] = '\0';
	write(STDOUT, &input->buffer[input->cursor_pos], input->len
		- input->cursor_pos);
	write(STDOUT, " ", 1);
	move_cursor = input->cursor_pos;
	while (move_cursor++ <= input->len)
		write(STDOUT, "\b", 1);
}

// Shifts the buffer one position to the left starting at cursor_pos.
// Redraws the modified buffer in STDOUT and moves the cursor back.
void	handle_backspace(t_input *input)
{
	unsigned int	move_cursor;

	if (input->cursor_pos <= 0)
		return ;
	ft_strmove(&input->buffer[input->cursor_pos - 1],
		&input->buffer[input->cursor_pos], input->len - input->cursor_pos);
	input->buffer = ft_realloc(input->buffer, input->len, input->len - 1);
	input->buffer[--input->len] = '\0';
	input->cursor_pos--;
	write(STDOUT, "\b", 3);
	write(STDOUT, &input->buffer[input->cursor_pos], input->len
		- input->cursor_pos);
	write(STDOUT, " \b", 4);
	move_cursor = input->cursor_pos;
	while (move_cursor++ < input->len)
		write(STDOUT, "\b", 1);
}

// Writes STDIN into STDOUT and dynamically stores it into a buffer.
// If cursor_pos is smaller:
// - Shifts the buffer one position to the left starting at cursor_pos.
// - Redraws the modified buffer in STDOUT and moves the cursor back.
void	handle_input(t_input *input, unsigned char character)
{
	unsigned int	move_cursor;

	if (input->cursor_pos >= input->len)
	{
		input->buffer = ft_realloc(input->buffer, input->len, input->len + 1);
		input->buffer[input->len] = character;
		input->buffer[++input->len] = '\0';
		write(STDOUT, &character, 1);
		input->cursor_pos++;
	}
	else
	{
		input->buffer = ft_realloc(input->buffer, input->len, input->len + 1);
		ft_strmove(&input->buffer[input->cursor_pos + 1],
			&input->buffer[input->cursor_pos], input->len - input->cursor_pos);
		input->buffer[input->cursor_pos++] = character;
		input->buffer[++input->len] = '\0';
		write(STDOUT, &input->buffer[input->cursor_pos - 1], input->len
			- input->cursor_pos + 1);
		move_cursor = input->len - input->cursor_pos;
		while (move_cursor-- > 0)
			write(STDOUT, "\b", 1);
	}
}
