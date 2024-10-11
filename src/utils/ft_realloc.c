/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:07:01 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/11 14:48:34 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	*ft_realloc(unsigned char *old_str, unsigned int old_length,
			unsigned int new_length)
{
	unsigned int	i;
	unsigned char	*new_str;

	new_str = (unsigned char)malloc(sizeof(char) * (new_length + 1));
	if (new_str == NULL)
		ft_perror(1);
	if (old_length >= new_length)
		ft_perror(0);
	i = 0;
	while (i < old_length)
	{
		new_str[i] = old_str[i];	
		i++;
	}
	free(old_str);
	return (new_str);
}
