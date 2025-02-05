/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:26:28 by andi              #+#    #+#             */
/*   Updated: 2025/02/05 13:51:07 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_var(char **env)
{
	unsigned int	i;
	char			*var;
	bool			found_var;

	i = 0;
	found_var = false;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5))
		{
			var = env[i] + 5;
			found_var = true;
		}
		i++;
	}
	if (!found_var)
	{
		printf(ERR"$HOME not found!\n");
		g_exit_status = 1;
		return (NULL);
	}
	return (var);
}

void	ft_cd(char **command, unsigned int nbr_of_cmd, char **env)
{
	char	*home_var;

	home_var = get_home_var(env);
	if (!home_var)
		return ;
	if (nbr_of_cmd == 1)
		chdir(home_var);
	else
	{
		if (chdir(command[1]) == -1)
		{
			printf(ERR"Not a directory!\n");
			g_exit_status = 1;
			return ;
		}
	}
}
