/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:25:12 by anvacca           #+#    #+#             */
/*   Updated: 2025/02/04 10:13:57 by flmarsou         ###   ########.fr       */
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

void	ft_echo(char **command, unsigned int nbr_of_cmd)
{
	unsigned int	i;
	bool			new_line;

	i = 1;
	new_line = false;
	if (nbr_of_cmd > i)
		new_line = is_newline(command[i]);
	if (new_line)
		i++;
	while (i < nbr_of_cmd)
	{
		ft_putstr(command[i]);
		if (i + 1 < nbr_of_cmd)
			write(1, " ", 1);
		i++;
	}
	if (!new_line)
		write(1, "\n", 1);
}
