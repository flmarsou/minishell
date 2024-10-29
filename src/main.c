/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/29 15:33:13 by anvacca          ###   ########.fr       */
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
		tokenizer(input.buffer, &lexer);		
		printf("%s | Lenght: %u | Cursor X: %u Y: %u\n", input.buffer, input.len, input.cursor_x, input.cursor_y); // Debug
		printf("Win X: %u Y: %u\n\n", input.term_x, input.term_y); // Debug
		for (size_t i = 0; lexer.str[i]; i++)
		{
			printf("%s %d\n", lexer.str[i], i);
			free(lexer.str[i]);
		}
		free(lexer.str);
		if (input.buffer)
			free(input.buffer);
	}
	disable_raw_mode(&orig_termios);
	return (0);
}
