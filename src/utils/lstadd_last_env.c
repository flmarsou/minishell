/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_last_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:04:01 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/06 13:13:41 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstadd_last_env(t_environ **environ, char *input)
{
	t_environ	*current;

	current = *environ;
	while (current && current->next)
	{
		current = current->next;
	}
	current->next = lstnew_env(input);
}
