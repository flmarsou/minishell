/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/24 14:19:08 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	struct termios	orig_termios;
	t_input			input;

	enable_raw_mode(&orig_termios);
	while (true)
	{
		read_user_input(&input);
		printf("%s | %u | %u\n\n", input.buffer, input.length, input.cursor_pos); // Debug
		if (input.buffer)
			free(input.buffer);
	}
	disable_raw_mode(&orig_termios);
	return (0);
}
