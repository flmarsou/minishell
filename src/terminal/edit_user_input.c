/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:33:07 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/31 13:48:30 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rewrite(t_input *input)
{
	unsigned int	i;
	unsigned int	erase;

	i = 0;
	erase = (input->len + input->term_x - 1) / input->term_x;
	while (i < erase)
	{
		write(STDOUT, CURSOR_DOWN, 3);
		i++;
	}
	while (erase >= 1)
	{
		write(STDOUT, CLEAR_LINE, 3);
		if (erase > 1)
			write(STDOUT, CURSOR_UP, 3);
		erase--;
	}
	write(STDOUT, CLEAR_LINE, 3);
	write(STDOUT, "\r", 1);
	write(STDOUT, input->buffer, input->len);
}

static void	write_front(t_input *input, unsigned char character)
{
	input->buffer[input->len] = character;
	input->buffer[++input->len] = '\0';
	write(STDOUT, &character, 1);
	input->cursor_x++;
	rewrite(input);
}

static void	write_middle(t_input *input, unsigned char character)
{
	unsigned int	i;

	i = 0;
	ft_strmove(&input->buffer[input->cursor_x + 1], &input->buffer[input->cursor_x], input->len - input->cursor_x + 1);
	input->buffer[input->cursor_x] = character;
	write(STDOUT, &character, 1);
	input->cursor_x++;
	input->len++;
	rewrite(input);
	// while (i < input->len - input->cursor_x)
	// {
	// 	arrow_key_left(input);
	// 	i++;
	// }
}

// Writes STDIN into STDOUT and dynamically stores it into a buffer.
void	handle_input(t_input *input, unsigned char character)
{
	if (input->len + 1 >= input->alloc_len)
	{
		input->alloc_len = ((input->len + CHUNK) / CHUNK) * CHUNK;
		input->buffer = ft_realloc(input->buffer, input->len, input->alloc_len);
	}
	if (input->cursor_x >= input->len)
		write_front(input, character);
	else
		write_middle(input, character);
}
