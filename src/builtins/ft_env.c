/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:25:55 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/12 15:01:10 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_environ *environ)
{
	while (environ)
	{
		if (!strchr(environ->var, '=')) // Add ft_strchr into Utils
			environ = (*environ).next;
		else
		{
			printf("%s\n", (*environ).var);
			environ = (*environ).next;
		}
	}
}
