/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:13:48 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/05 14:55:43 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_var(char ***env, unsigned int index)
{
	unsigned int	i;
	unsigned int	j;
	char			**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i));
	new_env[i - 1] = NULL;
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (i == index)
			i++;
		else
		{
			new_env[j] = ft_strdup((*env)[i]);
			i++;
			j++;
		}
	}
	free_env(env);
	*env = new_env;
}

void	ft_unset(char ***env, char **input, unsigned int nbr_of_cmd)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_str;
	unsigned int	len;

	j = 1;
	while (j < nbr_of_cmd)
	{
		if (!input[j])
		{
			j++;
			continue ;
		}
		i = 0;
		while ((*env)[i])
		{
			len_str = 0;
			len = 0;
			while (input[j][len_str] && input[j][len_str] != '=')
					len_str++;
			while ((*env)[i][len] && (*env)[i][len] != '=')
					len++;
			if (ft_strncmp((*env)[i], input[j], len) && len == len_str)
			{
				remove_var(env, i);
				break ;
			}
			i++;
		}
		j++;
	}
}
