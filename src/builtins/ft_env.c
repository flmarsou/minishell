/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:25:55 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/12 13:26:26 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_environ *environ)
{
	while (environ)
	{
		if (!strchr(environ->var, '='))
			environ = (*environ).next;
		else
		{
			printf("%s\n", (*environ).var);
			environ = (*environ).next;
		}
	}
}
