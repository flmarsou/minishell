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

unsigned char	*ft_realloc(unsigned char *old_str, unsigned int old_size, unsigned int new_size)
{
	unsigned int	i;
	unsigned char	*new_str;

	new_str = (unsigned char *)malloc(sizeof(unsigned char) * (new_size + 1));
	if (new_str == NULL)
		ft_perror(1);
	i = 0;
	while (i < old_size)
	{
		new_str[i] = old_str[i];	
		i++;
	}
	free(old_str);
	return (new_str);
}
