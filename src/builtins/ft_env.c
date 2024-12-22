/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andi <andi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:25:55 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/22 23:51:43 by andi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_environ *environ, unsigned int *builtin)
{
	*builtin = 1;
	while (environ)
	{
		if (!ft_strchr(environ->var, '='))
			environ = (*environ).next;
		else
		{
			printf("%s\n", (*environ).var);
			environ = (*environ).next;
		}
	}
}
