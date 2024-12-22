/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andi <andi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:25:12 by anvacca           #+#    #+#             */
/*   Updated: 2024/12/22 23:51:50 by andi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_newline(unsigned char *str)
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

void	ft_echo(char **args, unsigned int *builtin)
{
	unsigned int	i;
	bool			new_line;

	i = 0;
	*builtin = 1;
	new_line = is_newline(args[i]);
	if (new_line)
		i++;
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!new_line)
		write(1, "\n", 1);
}
