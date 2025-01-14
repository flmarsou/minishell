/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:10:02 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/14 12:25:48 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bubble_sort(t_environ *environ)
{
	char			**sorted_tab;
	bool			swapped;
	unsigned int	i;

	sorted_tab = export_copy_arr(environ);
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

static void	modify_env(t_environ **environ, char *input, unsigned int i,
		unsigned int j)
{
	t_environ	*current;
	bool		modified;

	current = *environ;
	modified = false;
	while (current)
	{
		i = 0;
		while (current->var[i + 1] && current->var[i + 1] != '=')
			i++;
		if (j == i)
		{
			if (ft_strncmp(input, current->var, j) == true)
			{
				modified = true;
				if (input[j + 1])
					current->var = input;
				else
					return ;
			}
		}
		current = current->next;
	}
	if (!modified)
		export_lstadd_last(environ, input);
}

void	ft_export(t_environ **environ, char **input, unsigned int nbr_of_cmd)
{
	unsigned int	j;
	unsigned int	i;

	i = 1;
	if (nbr_of_cmd == 1)
	{
		bubble_sort(*environ);
		return ;
	}
	while (i < nbr_of_cmd)
	{
		if (input[i] && input[i][0] == '=')
		{
			write(1, "\e[1;97mExport: '=': not a valid identifier!\n\e[0m", 48);
			return ;
		}
		else
		{
			j = 0;
			while (input[i][j + 1] && input[i][j + 1] != '=')
				j++;
			modify_env(environ, input[i], 0, j);
		}
		i++;
	}
}
