/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:29:59 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/24 14:30:35 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *str1, char *str2)
{
	unsigned int	i;
	unsigned int	j;
	char			*ret;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!ret)
		return (NULL);
	while (str1[i])
	{
		ret[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		ret[i + j] = str2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}
