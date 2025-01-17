/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:08:48 by anvacca           #+#    #+#             */
/*   Updated: 2025/01/17 12:26:01 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bubble_sort(char **env)
{
	char			**sorted_tab;
	bool			swapped;
	unsigned int	i;

	sorted_tab = export_copy_arr(env);
	swapped = true;
	while (swapped)
	{
		swapped = false;
		i = 0;
		while (sorted_tab[i] && sorted_tab[i + 1])
		{
			if (strcmp(sorted_tab[i], sorted_tab[i + 1]) > 0)
			{
				export_swap_vars(&sorted_tab[i], &sorted_tab[i + 1]);
				swapped = true;
			}
			i++;
		}
	}
	i = 0;
	while (sorted_tab[i])
		export_print(sorted_tab[i++]);
	free(sorted_tab);
}

bool	check_input(char *str)
{
	unsigned int	i;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		printf("Syntax error, unexpected '%c' in \"%s\"\n", str[0], str);
		return (false);
	}
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("Syntax error, unexpected '%c' in \"%s\"\n", str[i], str);
			return (false);
		}
		i++;
	}
	return (true);
}

void	export_print(char *str)
{
	unsigned int	i;
	bool			is_defined;

	i = 0;
	is_defined = false;
	write(1, "export ", 7);
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
