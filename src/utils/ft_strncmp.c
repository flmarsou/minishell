/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:15:56 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/07 10:56:13 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strncmp(char *str1, char *str2, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while ((str1[i] || str2[i]) && i < size)
	{
		if (str1[i] != str2[i])
			return (false);
		i++;
	}
	return (true);
}
