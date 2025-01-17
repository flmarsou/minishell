/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:13:48 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/17 15:06:07 by anvacca          ###   ########.fr       */
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
			if (ft_strncmp((*env)[i], input[j], ft_strlen(input[j])))
			{
				remove_var(env, i);
				break ;
			}
			i++;
		}
		j++;
	}
}
