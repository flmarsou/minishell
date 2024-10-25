/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:13:14 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/25 12:18:48 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	*ft_strcpy(unsigned char *dest, unsigned char *src,
		unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
