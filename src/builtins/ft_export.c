/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:10:02 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/06 15:28:32 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_vars(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

static char	**copy_tab(t_environ *environ)
{
	char			**unsorted_tab;
	unsigned int	i;

	unsorted_tab = malloc(sizeof(char *) * (ft_lstsize(environ) + 1));
	i = 0;
	while (environ)
	{
		unsorted_tab[i] = environ->var;
		environ = environ->next;
		i++;
	}
	unsorted_tab[i] = NULL;
	return (unsorted_tab);
}

static void	bubble_sort(t_environ *environ)
{
	char			**sorted_tab;
	bool			swapped;
	unsigned int	i;

	sorted_tab = copy_tab(environ);
	swapped = true;
	while (swapped)
	{
		swapped = false;
		i = 0;
		while (sorted_tab[i] && sorted_tab[i + 1])
		{
			if (strcmp(sorted_tab[i], sorted_tab[i + 1]) > 0)
			{
				swap_vars(&sorted_tab[i], &sorted_tab[i + 1]);
				swapped = true;
			}
			i++;
		}
	}
	i = 0;
	while (sorted_tab[i])
		ft_export_print(sorted_tab[i++]);
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
	{
		puts("in");
		lstadd_last_env(environ, input);
	}
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
