/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/31 13:52:17 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	struct termios	orig_termios;
	t_input			input;
	t_lexer			lexer;

	enable_raw_mode(&orig_termios);
	get_terminal_size(&input);
	while (true)
	{
		read_user_input(&input);
		printf("%s | Lenght: %u\nCursor X: %u\nNbr of Lines: %u\n", input.buffer, input.len, input.cursor_x, input.term_lines); // Debug
		printf("Window Width: %u\n", input.term_x); // Debug
		if (input.buffer)
			free(input.buffer);
	}
	disable_raw_mode(&orig_termios);
	return (0);
}
