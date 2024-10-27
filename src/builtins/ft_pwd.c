/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andi <andi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:54:08 by andi              #+#    #+#             */
/*   Updated: 2024/10/27 17:24:24 by andi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static unsigned int ft_strlen(char *string)
{
	unsigned int i;

	i = 0;
	while(string[i])
		i++;
	return(i);
}

bool	ft_pwd(void)
{
	char current_path[PATH_MAX];

	if (!getcwd(current_path, sizeof(current_path)))
	{
		write(1, "error message\n", 14);
		return (false);
	}
	else
	{
		write(1, &current_path, ft_strlen(current_path));
		return(true);	
	}
	return(false);
}

// int main()
// {
// 	ft_pwd();
// }