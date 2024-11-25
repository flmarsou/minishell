/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:24:36 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/25 15:26:09 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strerror(const char *str)
{
	unsigned int	i;

	i = 0;
	write(STDOUT, "\e[1;31m[x] - Error: \e[1;97m", 27);
	while (str[i])
	{
		write(STDOUT, &str[i], 1);
		i++;
	}
	write(STDOUT, "\n", 1);
}
