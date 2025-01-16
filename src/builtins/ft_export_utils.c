/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:08:48 by anvacca           #+#    #+#             */
/*   Updated: 2025/01/16 15:44:15 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_print(char *str)
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

void	export_swap_vars(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

char	**export_copy_arr(char **env)
{
	char			**unsorted_arr;
	unsigned int	i;

	i = 0;
	while (env[i])
		i++;
	unsorted_arr = malloc(sizeof(char *) * (i + 1));
	unsorted_arr[i] = NULL;
	i = 0;
	while (env[i])
	{
		unsorted_arr[i] = env[i];
		i++;
	}
	return (unsorted_arr);
}
