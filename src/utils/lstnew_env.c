/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:04:22 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/12 09:04:40 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environ	*lstnew_env(char *var)
{
	t_environ	*new;

	new = malloc(sizeof(t_environ));
	if (!new)
		ft_perror(1);
	new->var = var;
	new->next = NULL;
	return (new);
}
