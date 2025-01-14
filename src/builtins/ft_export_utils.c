/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:08:48 by anvacca           #+#    #+#             */
/*   Updated: 2025/01/14 12:25:36 by flmarsou         ###   ########.fr       */
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

char	**export_copy_arr(t_environ *environ)
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

void	export_lstadd_last(t_environ **environ, char *input)
{
	t_environ	*current;

	current = *environ;
	while (current && current->next)
	{
		current = current->next;
	}
	current->next = lstnew_env(input);
}
