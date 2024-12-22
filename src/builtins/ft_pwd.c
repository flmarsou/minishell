/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andi <andi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:54:08 by andi              #+#    #+#             */
/*   Updated: 2024/12/22 23:51:29 by andi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_pwd(unsigned int *builtin)
{
	unsigned char	current_path[PATH_MAX];

	*builtin = 1;
	if (!getcwd(current_path, sizeof(current_path)))
	{
		write(1, "error message\n", 14);
		return (false);
	}
	else
	{
		write(1, &current_path, ft_strlen(current_path));
		return (true);
	}
	return (false);
}
