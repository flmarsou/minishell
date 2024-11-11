/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:10:02 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/11 16:09:19 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_vars(unsigned char **str1, unsigned char **str2)
{
	unsigned char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

static unsigned char	**copy_tab(t_environ *environ)
{
	unsigned char	**unsorted_tab;
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
	unsigned char	**sorted_tab;
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
			if (ft_strcmp(sorted_tab[i], sorted_tab[i + 1]) > 0)
			{
				swap_vars(&sorted_tab[i], &sorted_tab[i + 1]);
				swapped = true;
			}
			i++;
		}
	}
	i = 0;
	while (sorted_tab[i])
		printf("%s\n", sorted_tab[i++]);
	free(sorted_tab);
}

void	ft_export(t_environ **environ, unsigned char *input)
{
	unsigned int	i;

	i = 0;
	if (!input)
		bubble_sort(*environ);
	else
	{
		while (environ[i] != '=')
			i++;
		if (ft_strncmp(input, (*environ)->var, ))
		{
			// Takes size of both until '='
			// Compares if sizes are equal
			// If not, strcmp
		}
		
	}
}
