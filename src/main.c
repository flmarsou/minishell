/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/05 10:57:54 by flmarsou         ###   ########.fr       */
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
		// Debug
		fprintf(stderr, "%s\n", input.buffer);
		fprintf(stderr, "Length:       %u\n", input.cursor_x);
		fprintf(stderr, "Alloc Length: %u\n", input.alloc_len);
		fprintf(stderr, "Cursor X:     %u\n", input.cursor_x);
		fprintf(stderr, "Term Lines:   %u\n", input.term_lines);
		fprintf(stderr, "Term Width:   %u\n\n", input.term_x);
		if (input.buffer)
			free(input.buffer);
	}
	disable_raw_mode(&orig_termios);
	return (0);
}
