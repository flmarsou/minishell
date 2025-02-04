/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:54:08 by andi              #+#    #+#             */
/*   Updated: 2025/02/04 09:57:45 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	current_path[PATH_MAX];

	if (!getcwd(current_path, sizeof(current_path)))
	{
		printf(ERR"Function getcwd failed!\n");
		exit(1);
	}
	else
	{
		write(1, &current_path, ft_strlen(current_path));
		write(1, "\n", 1);
	}
	exit(0);
}
