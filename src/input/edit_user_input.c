/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:33:07 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/24 15:45:57 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_delete(t_input *input)
{
	unsigned int	move_cursor;

	if (input->cursor_pos >= input->length)
		return ;
	memmove(&input->buffer[input->cursor_pos], &input->buffer[input->cursor_pos + 1], input->length - input->cursor_pos - 1);
	input->length--;
	write(STDOUT, &input->buffer[input->cursor_pos], input->length - input->cursor_pos);
	write(STDOUT, " ", 1);
	move_cursor = input->cursor_pos - 1;
	while (move_cursor++ < input->length)
		write(STDOUT, "\b", 1);
	input->buffer[input->length] = '\0';
}

void	handle_backspace(t_input *input)
{
	unsigned int	move_cursor;

	if (input->cursor_pos <= 0)
		return ;
	write(STDOUT, "\b", 3);
	memmove(&input->buffer[input->cursor_pos - 1], &input->buffer[input->cursor_pos], input->length - input->cursor_pos);
	input->length--;
	input->cursor_pos--;
	move_cursor = input->cursor_pos;
	write(STDOUT, &input->buffer[input->cursor_pos], input->length - input->cursor_pos);
	write(STDOUT, " \b", 4);
	while (move_cursor++ < input->length)
		write(STDOUT, "\b", 1);
	input->buffer[input->length] = '\0';
}

void	handle_input(t_input *input, unsigned char character)
{
	input->cursor_pos++;
	write(STDOUT, &character, 1);
	input->buffer = ft_realloc(input->buffer, input->length, input->length + 1);
	input->buffer[input->length] = character;
	input->buffer[++input->length] = '\0';
}
