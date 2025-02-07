/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:02:29 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/07 10:11:11 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_next_path(char *str, unsigned int *i)
{
	unsigned int		j;
	char				*current_path;

	j = 0;
	current_path = malloc(sizeof(char) * 256);
	while (str[*i])
	{
		if (str[*i] == ':')
		{
			(*i)++;
			break ;
		}
		if (j < 254)
		{
			current_path[j] = str[*i];
			j++;
		}
		(*i)++;
	}
	current_path[j] = '/';
	current_path[++j] = '\0';
	return (current_path);
}

static unsigned int	count_paths(char *str)
{
	unsigned int	nbr_of_paths;
	unsigned int	i;

	nbr_of_paths = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == ':')
			nbr_of_paths++;
		i++;
	}
	return (nbr_of_paths);
}

static char	*get_path_var(char **env)
{
	unsigned int	i;
	char			*var;
	bool			found_var;

	i = 0;
	found_var = false;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5))
		{
			var = env[i] + 5;
			found_var = true;
		}
		i++;
	}
	if (!found_var)
	{
		ft_putstr_fd(ERR"Command not found!\n", 2);
		exit(127);
	}
	return (var);
}

static void	find_exec(char *path_var, char **command, char **env)
{
	unsigned int	nbr_of_paths;
	char			*current_path;
	char			*full_path;
	unsigned int	index;

	index = 0;
	nbr_of_paths = count_paths(path_var);
	while (nbr_of_paths)
	{
		current_path = get_next_path(path_var, &index);
		if (current_path)
		{
			full_path = ft_strjoin(current_path, command[0]);
			free(current_path);
			if (access(full_path, F_OK) == 0)
				execve(full_path, command, env);
			free(full_path);
		}
		nbr_of_paths--;
	}
}

void	ft_execve(char **command, char **env)
{
	char			*path_var;

	if (access(command[0], F_OK) == 0)
		execve(command[0], command, env);
	path_var = get_path_var(env);
	if (!path_var)
	{
		ft_putstr_fd(ERR"No PATH found, cannot execute commands!\n", 2);
		exit(127);
	}
	if (access(command[0], F_OK) == 0)
		execve(command[0], command, env);
	find_exec(path_var, command, env);
	ft_putstr_fd(ERR"Command \"", 2);
	ft_putstr_fd(command[0], 2);
	ft_putstr_fd("\" not found!", 2);
	exit(127);
}
