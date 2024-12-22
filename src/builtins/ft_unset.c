/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andi <andi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:13:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/22 23:51:21 by andi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_environ **environ, char *input, unsigned int *builtin)
{
	t_environ	*save;
	t_environ	*current;

	*builtin = 1;
	current = *environ;
	if (!input)
		return ;
	while (current)
	{
		if (current->next && ft_strcmp(current->next->var, input) == 0)
		{
			save = current->next;
			current->next = current->next->next;
			free(save);
			break ;
		}
		current = current->next;
	}
}
