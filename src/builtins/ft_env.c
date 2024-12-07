/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:25:55 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/25 11:40:12 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_environ *environ)
{
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
