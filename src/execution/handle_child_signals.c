/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child_signals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:06:17 by anvacca           #+#    #+#             */
/*   Updated: 2025/02/05 11:06:44 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal_child(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDOUT, "\n", 1);
		rl_redisplay();
	}
}

void	handle_signal_child_kill(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(STDOUT, "Quit (core dumped)\n", 19);
	rl_redisplay();
}
