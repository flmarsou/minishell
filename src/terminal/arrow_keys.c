/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:28:43 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/31 12:56:04 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arrow_key_left(t_input *input)
{
	unsigned int	i;

	i = 0;
	if (input->cursor_x % input->term_x == 0)
	{
		write(1, CURSOR_UP, 3);
		while (i++ < input->term_x)
			write(1, CURSOR_RIGHT, 3);
	}
	else
		write(1, CURSOR_LEFT, 3);
}

void	arrow_key_right(t_input *input)
{
	unsigned int	i;

	i = 0;
	if ((input->cursor_x + 1) % input->term_x == 0)
	{
		write(1, CURSOR_DOWN, 3);
		while (i++ < input->term_x)
			write(1, CURSOR_LEFT, 3);
	}
	else
		write(1, CURSOR_RIGHT, 3);
}
