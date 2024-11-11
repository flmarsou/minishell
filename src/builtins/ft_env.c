/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:25:55 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:51 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_environ *environ)
{
	unsigned int	i;

	i = 0;
	while (environ)
	{
		printf("%s\n", (*environ).var);
		environ = (*environ).next;
	}
}
