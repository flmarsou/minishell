/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:10:02 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/16 15:58:42 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bubble_sort(char **env)
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

static void	modify_env(char ***env, char *input)
{
	
}

void	ft_export(char ***env, char **input, unsigned int nbr_of_cmd)
{
	unsigned int	j;
	unsigned int	i;

	i = 1;
	if (nbr_of_cmd == 1)
	{
		bubble_sort(*env);
		return ;
	}
	while (i < nbr_of_cmd)
	{
		if (input[i] && input[i][0] == '=') // TODO: Add conditions for naming
		{
			write(1, "\e[1;97mExport: '=': not a valid identifier!\n\e[0m", 48);
			return ;
		}
		else
		{
			// TODO: Add if not already exist
		}
		i++;
	}
}
