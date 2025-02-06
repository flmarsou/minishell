/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:10:17 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/06 10:52:55 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool check_arg(char *str)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			i++;
			len++;
		}
		else
			return (false);
	}
	if (len <= 20)
		return (true);
	return (false);
}

void	ft_exit(char **command, unsigned int nbr_of_cmd)
{
	bool	valid_arg;

	if (nbr_of_cmd == 1)
		exit(0);
	valid_arg = check_arg(command[1]);
	if (!valid_arg)
	{
		printf(SERR"Numeric argument required!\n");
		exit(2);
	}
	else if (valid_arg && nbr_of_cmd == 2)
		exit(ft_atol(command[1]) % 256);
	printf(WARN"Too many arguments!\n");
}
