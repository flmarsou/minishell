/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:05:14 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/11 14:06:59 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_lstsize(t_environ *environ)
{
	unsigned int	i;

	i = 0;
	if (environ == NULL)
		return (0);
	while (environ)
	{
		environ = environ->next;
		i++;
	}
	return (i);
}
