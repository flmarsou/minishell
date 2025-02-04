/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:10:02 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/04 11:17:13 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_var(char ***env, char *str)
{
	unsigned int	i;
	unsigned int	j;
	char			**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		new_env[j] = ft_strdup((*env)[i]);
		i++;
		j++;
	}
	new_env[j] = ft_strdup(str);
	new_env[j + 1] = NULL;
	free_env(env);
	*env = new_env;
}

static void	edit_env(char ***env, char *str)
{
	unsigned int	len;
	unsigned int	i;

	len = 0;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		len++;
		i++;
	}
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], str, len))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(str);
			return ;
		}
		i++;
	}
	add_var(env, str);
}

static bool	check_input(char *str)
{
	unsigned int	i;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		printf(SERR"Unexpected '%c' in \"%s\"\n", str[0], str);
		g_exit_status = 1;
		return (false);
	}
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf(SERR"Unexpected '%c' in \"%s\"\n", str[i], str);
			g_exit_status = 1;
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_export(char ***env, char **input, unsigned int nbr_of_cmd)
{
	unsigned int	i;

	i = 1;
	if (nbr_of_cmd == 1)
	{
		bubble_sort(*env);
		return ;
	}
	while (i < nbr_of_cmd)
	{
		if (!check_input(input[i]))
			i++;
		else
			edit_env(env, input[i]);
		i++;
	}
}
