/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:08:48 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/12 14:08:41 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_print(char *str)
{
	unsigned int	i;
	bool			is_defined;

	i = 0;
	is_defined = false;
	while (str[i])
	{
		write(1, &str[i], 1);
		if (str[i] == '=')
		{
			write(1, "\"", 1);
			is_defined = true;
		}
		i++;
	}
	if (is_defined == true)
		write(1, "\"\n", 2);
	else
		write(1, "\n", 1);
}
