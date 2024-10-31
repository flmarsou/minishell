/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_terminal_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:53:21 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/30 15:37:32 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_input	*get_input_instance(t_input *input)
{
	static t_input	*input_instance = NULL;

	if (input)
		input_instance = input;
	return (input_instance);
}

static void	handle_winsize(void)
{
	t_input			*input;
	struct winsize	ws;

	input = get_input_instance(NULL);
	if (ioctl(STDOUT, TIOCGWINSZ, &ws) == -1)
		ft_perror(2);
	input->term_x = ws.ws_col;
}

static void	handle_sigwinch(int sig)
{
	(void)sig;
	handle_winsize();
}

void	get_terminal_size(t_input *input)
{
	struct winsize	ws;

	if (ioctl(STDOUT, TIOCGWINSZ, &ws) == -1)
		ft_perror(2);
	input->term_x = ws.ws_col;
	get_input_instance(input);
	signal(SIGWINCH, handle_sigwinch);
}
