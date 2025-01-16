/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:25:12 by anvacca           #+#    #+#             */
/*   Updated: 2025/01/16 12:25:00 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_newline(char *str)
{
	unsigned int	i;

	i = 0;
	if (str[i++] == '-' && str[i] && str[i] == 'n')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] && str[i] != 'n')
			return (false);
	}
	else
		return (false);
	return (true);
}

void	ft_echo(char **command, unsigned int argc)
{
	unsigned int	i;
	bool			new_line;

	i = 1;
	new_line = false;
	if (argc > i)
		new_line = is_newline(command[i]);
	if (new_line)
		i++;
	while (i < argc)
	{
		ft_putstr(command[i]);
		if (i + 1 < argc)
			write(1, " ", 1);
		i++;
	}
	if (!new_line)
		write(1, "\n", 1);
}
