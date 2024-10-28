/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/28 13:27:10 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	struct termios	orig_termios;
	t_input			input;

	enable_raw_mode(&orig_termios);
	get_terminal_size(&input);
	while (true)
	{
		read_user_input(&input);
		printf("%s | Lenght: %u | Cursor X: %u Y: %u\n", input.buffer, input.len, input.cursor_x, input.cursor_y); // Debug
		printf("Win X: %u Y: %u\n\n", input.term_x, input.term_y); // Debug
		if (input.buffer)
			free(input.buffer);
	}
	disable_raw_mode(&orig_termios);
	return (0);
}
