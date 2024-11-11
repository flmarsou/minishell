/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:43:57 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/11 12:46:24 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstfree(t_environ *environ)
{
	t_environ	*temp;

	while (environ)
	{
		temp = environ->next;
		free(environ);
		environ = temp;
	}
}
