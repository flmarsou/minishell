/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:05:26 by anvacca           #+#    #+#             */
/*   Updated: 2025/02/05 11:05:47 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(t_parser *parser, unsigned int groups)
{
	unsigned int	i;

	i = 0;
	while (i < groups - 1)
	{
		pipe(parser[i].fd);
		i++;
	}
}

void	close_unused_pipes(t_parser *parser, unsigned int groups,
		unsigned int i)
{
	unsigned int	j;

	j = 0;
	while (j < groups - 1)
	{
		if (j == i)
			close(parser[j].fd[0]);
		else if (j == i - 1)
			close(parser[j].fd[1]);
		else
		{
			close(parser[j].fd[0]);
			close(parser[j].fd[1]);
		}
		j++;
	}
}

void	pipes(t_parser *parser, unsigned int groups, unsigned int i)
{
	if (i == 0)
	{
		dup2(parser[i].fd[1], STDOUT);
		close(parser[i].fd[1]);
	}
	else if (i < groups - 1)
	{
		close(parser[i].fd[0]);
		dup2(parser[i - 1].fd[0], STDIN);
		close(parser[i - 1].fd[0]);
		dup2(parser[i].fd[1], STDOUT);
		close(parser[i].fd[1]);
	}
	else
	{
		dup2(parser[i - 1].fd[0], STDIN);
		close(parser[i - 1].fd[0]);
	}
}
