/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:13:48 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/06 15:12:42 by anvacca          ###   ########.fr       */
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
		if (current->next && ft_strcmp(current->next->var, input))
		{
			save = current->next;
			current->next = current->next->next;
			free(save);
			break ;
		}
		current = current->next;
	}
}
