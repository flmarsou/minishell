/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:10:02 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/07 09:58:11 by anvacca          ###   ########.fr       */
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
	unsigned int	len_str;

	i = 0;
	len_str = 0;
	while (str[len_str] && str[len_str] != '=')
		len_str++;
	while ((*env)[i])
	{
		len = 0;
		while ((*env)[i][len] && (*env)[i][len] != '=')
			len++;
		if (ft_strncmp((*env)[i], str, len) && len == len_str)
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
		ft_putstr_fd(SERR"Unexpected '", 2);
		write(2, &str[0], 1);
		ft_putstr_fd("' in \"", 2);
		ft_putstr_fd(str, 2);
		return (ft_putstr_fd("\"\n", 2), false);
	}
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_fd(SERR"Unexpected '", 2);
			write(2, &str[i], 1);
			ft_putstr_fd("' in \"", 2);
			ft_putstr_fd(str, 2);
			return (ft_putstr_fd("\"\n", 2), false);
		}
		i++;
	}
	return (true);
}

bool	ft_export(char ***env, char **input,
			unsigned int nbr_of_cmd)
{
	unsigned int	i;
	bool			ret;

	i = 1;
	ret = 0;
	if (nbr_of_cmd == 1)
	{
		bubble_sort(*env);
		return (0);
	}
	while (i < nbr_of_cmd)
	{
		if (!check_input(input[i]))
		{
			ret = 1;
			i++;
		}
		else
			edit_env(env, input[i]);
		i++;
	}
	return (ret);
}
