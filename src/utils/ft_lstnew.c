/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:37:36 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/11 15:49:08 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environ	*ft_lstnew(unsigned char *var)
{
	t_environ	*new;

	new = malloc(sizeof(t_environ));
	if (!new)
		ft_perror(1);
	new->var = var;
	new->next = NULL;
	return (new);
}
