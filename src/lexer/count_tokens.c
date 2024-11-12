/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:09:18 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/12 14:07:22 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	count_tokens(char *str)
{
	unsigned int	i;
	unsigned int	wordcount;

	i = 0;
	wordcount = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] == str[i]
			&& (str[i++] && str[i++]))
			wordcount++;
		else if (ft_ismeta(str[i]) && !ft_isspace(str[i++]))
			wordcount++;
		if (ft_isspace(str[i]))
			wordcount++;
		while (ft_isspace(str[i]))
			i++;
		if (ft_isprint(str[i]) && !ft_ismeta(str[i]) && !ft_isspace(str[i++]))
			wordcount++;
		while (ft_isprint(str[i]) && !ft_ismeta(str[i]) && !ft_isspace(str[i]))
			i++;
	}
	return (wordcount);
}
