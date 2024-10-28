/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_terminal_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:53:21 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/28 14:26:49 by flmarsou         ###   ########.fr       */
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
	input->term_y = ws.ws_row;
}

static void	handle_sigwinch(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	handle_winsize();
}

void	get_terminal_size(t_input *input)
{
	struct sigaction	sa;

	get_input_instance(input);
	sa.sa_sigaction = handle_sigwinch;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGWINCH, &sa, NULL) == -1)
		ft_perror(2);
	handle_winsize();
}
