/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:33:07 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/28 12:49:19 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Shifts the buffer one position to the right starting at cursor_x.
// Redraws the modified buffer in STDOUT and moves the cursor back.
void	handle_delete(t_input *input)
{
	unsigned int	move_cursor;

	if (input->cursor_x >= input->len)
		return ;
	ft_strmove(&input->buffer[input->cursor_x],
		&input->buffer[input->cursor_x + 1], input->len - input->cursor_x
		- 1);
	input->buffer = ft_realloc(input->buffer, input->len, input->len - 1);
	input->buffer[--input->len] = '\0';
	write(STDOUT, &input->buffer[input->cursor_x], input->len
		- input->cursor_x);
	write(STDOUT, " ", 1);
	move_cursor = input->cursor_x;
	while (move_cursor++ <= input->len)
		write(STDOUT, "\b", 1);
}

// Shifts the buffer one position to the left starting at cursor_x.
// Redraws the modified buffer in STDOUT and moves the cursor back.
void	handle_backspace(t_input *input)
{
	unsigned int	move_cursor;

	if (input->cursor_x <= 0)
		return ;
	ft_strmove(&input->buffer[input->cursor_x - 1],
		&input->buffer[input->cursor_x], input->len - input->cursor_x);
	input->buffer = ft_realloc(input->buffer, input->len, input->len - 1);
	input->buffer[--input->len] = '\0';
	input->cursor_x--;
	write(STDOUT, "\b", 3);
	write(STDOUT, &input->buffer[input->cursor_x], input->len
		- input->cursor_x);
	write(STDOUT, " \b", 4);
	move_cursor = input->cursor_x;
	while (move_cursor++ < input->len)
		write(STDOUT, "\b", 1);
}

// Writes STDIN into STDOUT and dynamically stores it into a buffer.
// If cursor_x is smaller:
// - Shifts the buffer one position to the left starting at cursor_x.
// - Redraws the modified buffer in STDOUT and moves the cursor back.
void	handle_input(t_input *input, unsigned char character)
{
	unsigned int	move_cursor;

	if (input->cursor_x >= input->len)
	{
		input->buffer = ft_realloc(input->buffer, input->len, input->len + 1);
		input->buffer[input->len] = character;
		input->buffer[++input->len] = '\0';
		write(STDOUT, &character, 1);
		input->cursor_x++;
	}
	else
	{
		input->buffer = ft_realloc(input->buffer, input->len, input->len + 1);
		ft_strmove(&input->buffer[input->cursor_x + 1],
			&input->buffer[input->cursor_x], input->len - input->cursor_x);
		input->buffer[input->cursor_x++] = character;
		input->buffer[++input->len] = '\0';
		write(STDOUT, &input->buffer[input->cursor_x - 1], input->len
			- input->cursor_x + 1);
		move_cursor = input->len - input->cursor_x;
		while (move_cursor-- > 0)
			write(STDOUT, "\b", 1);
	}
}
