/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:20:31 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/12 12:08:14 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environ	*ft_lstadd_last(t_environ **environ, char *input)
{
	t_environ	*current;

	current = *environ;
	while (current && current->next)
	{
		current = current->next;
	}
	current->next = ft_lstnew(input);
	return (current);
}
