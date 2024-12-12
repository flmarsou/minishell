/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_last_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:04:01 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/12 09:04:11 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environ	*lstadd_last_env(t_environ **environ, char *input)
{
	t_environ	*current;

	current = *environ;
	while (current && current->next)
	{
		current = current->next;
	}
	current->next = lstnew_env(input);
	return (current);
}
