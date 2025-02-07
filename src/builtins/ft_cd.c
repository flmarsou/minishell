/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:26:28 by andi              #+#    #+#             */
/*   Updated: 2025/02/07 09:53:20 by anvacca          ###   ########.fr       */
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
		ft_putstr_fd(ERR"$HOME not found!\n", 2);
		return (NULL);
	}
	return (var);
}

static char	*get_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd(ERR"Failed to get current working directory!\n", 2);
		return (NULL);
	}
	return (cwd);
}

static void	modify_pwd(char ***env)
{
	unsigned int	i;
	char			*cwd;
	char			*new_pwd;

	i = 0;
	cwd = get_cwd();
	if (!cwd)
		return ;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], "PWD=", 4))
		{
			new_pwd = malloc(sizeof(char) * ft_strlen(cwd) + 5);
			ft_strcpy(new_pwd, "PWD=");
			ft_strcat(new_pwd, cwd);
			free((*env)[i]);
			(*env)[i] = new_pwd;
			free(cwd);
			return ;
		}
		i++;
	}
	ft_putstr_fd(WARN"$PWD not found!\n", 2);
	free(cwd);
}

static void	modify_oldpwd(char ***env)
{
	unsigned int	i;
	char			*cwd;
	char			*new_pwd;

	i = 0;
	cwd = get_cwd();
	if (!cwd)
		return ;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], "OLDPWD=", 7))
		{
			new_pwd = malloc(sizeof(char) * ft_strlen(cwd) + 8);
			ft_strcpy(new_pwd, "OLDPWD=");
			ft_strcat(new_pwd, cwd);
			free((*env)[i]);
			(*env)[i] = new_pwd;
			free(cwd);
			return ;
		}
		i++;
	}
	ft_putstr_fd(WARN"$OLDPWD not found!\n", 2);
	free(cwd);
}

bool	ft_cd(char **command, unsigned int nbr_of_cmd, char ***env)
{
	char	*home_var;

	home_var = get_home_var(*env);
	modify_oldpwd(env);
	if (nbr_of_cmd > 2)
		return (ft_putstr_fd(ERR"Too many arguments!\n", 2), 1);
	if (!home_var)
		return (1);
	if (nbr_of_cmd == 1)
	{
		chdir(home_var);
		modify_pwd(env);
	}
	else
	{
		if (chdir(command[1]) == -1)
		{
			ft_putstr_fd(ERR"Not a directory!\n", 2);
			return (1);
		}
		else
			modify_pwd(env);
	}
	return (0);
}
