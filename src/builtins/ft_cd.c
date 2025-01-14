/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:26:28 by andi              #+#    #+#             */
/*   Updated: 2025/01/06 15:12:17 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_cd(char *next_path)
{
	char			current_path[PATH_MAX];
	unsigned int	i;
	unsigned int	j;

	j = 0;
	if (!getcwd(current_path, sizeof(current_path)))
		return (false);
	i = ft_strlen(current_path);
	if (i + ft_strlen(next_path) > PATH_MAX)
		return (false);
	i++;
	current_path[i++] = '/';
	while (next_path[j])
	{
		current_path[i] = next_path[j];
		i++;
		j++;
	}
	current_path[i] = "\0";
	if (chdir(current_path) != 0)
		return (false);
	return (true);
}
