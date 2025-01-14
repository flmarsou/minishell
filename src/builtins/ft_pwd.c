/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:54:08 by andi              #+#    #+#             */
/*   Updated: 2025/01/06 15:12:35 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_pwd()
{
	char	current_path[PATH_MAX];

	if (!getcwd(current_path, sizeof(current_path)))
	{
		write(1, "error message\n", 14);
		return (false);
	}
	else
	{
		write(1, &current_path, ft_strlen(current_path));
		write(1, "\n", 1);
		return (true);
	}
	return (false);
}
