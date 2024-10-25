/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:57:23 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/25 12:18:51 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	*ft_strmove(unsigned char *dest, unsigned char *src,
		unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	if (dest < src)
	{
		while (i < size)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else if (dest > src)
	{
		while (size > 0)
		{
			dest[size - 1] = src[size - 1];
			size--;
		}
	}
	return (dest);
}
