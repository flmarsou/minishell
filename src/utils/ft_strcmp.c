/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:13:15 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/24 15:19:12 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strcmp(char *str1, char *str2)
{
	unsigned int	i;

	i = 0;
	if (str1[0] == '\0')
		return (false);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i++;
	}
	return (true);
}
