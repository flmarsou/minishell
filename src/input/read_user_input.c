/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:49:16 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/22 09:21:33 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	process_control_characters(t_input *input, unsigned char character)
{
	if (input->buffer)
		free(input->buffer);
	input->length = 0;
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

static bool	handle_input(t_input *input)
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
			return (process_control_characters(input, character));
		if (ft_isprint(character))
		{
			write(STDOUT, &character, 1);
			input->buffer = ft_realloc(input->buffer, input->length, input->length + 2);
			input->buffer[input->length] = character;
			input->buffer[++input->length] = '\0';
		}
	}
	return (true);
}

void	read_user_input(void)
{
	t_input	input;
	struct termios	orig_termios;

	enable_raw_mode(&orig_termios);
	while (true)
	{
		input.length = 0;
		input.buffer = NULL;
		if (handle_input(&input) == false)
			break ;
		write(STDOUT, "\n", 1);
		printf("%s | %u\n\n", input.buffer, input.length); // Debug
		// tokenizer(input.buffer);
		if (input.buffer)
			free(input.buffer);
	}
	disable_raw_mode(&orig_termios);
}
