/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:13:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/12 15:10:48 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_environ **environ, char *input)
{
	t_environ	*save;
	t_environ	*current;

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
