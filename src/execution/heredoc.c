/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:00:15 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/06 15:42:58 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_name(unsigned int count)
{
	char				*ret;
	char				*itoa;

	itoa = ft_itoa(count);
	ret = ft_strjoin(".heredoc_", itoa);
	free(itoa);
	return (ret);
}

static char	*print_env_var(char **env, int length, char *input)
{
	unsigned int	i;
	char			*var;
	bool			found_var;

	i = 0;
	found_var = false;
	while (env[i])
	{
		if (ft_strncmp(env[i], input, length))
		{
			var = env[i] + length + 1;
			found_var = true;
		}
		i++;
	}
	if (!found_var)
		return ("\a");
	return (var);
}

static void	expand_h(char *input, char **env, int fd)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (input[i])
	{
		while (input[i] && input[i] != '$')
			write(fd, &input[i++], 1);
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '\0' || input[i] == ' ')
				write(fd, "$", 1);
			else
			{
				j = i;
				while (input[j] && (input[j] != ' ' && input[j] != '='))
					j++;
				ft_putstr_fd(print_env_var(env, j - i, input + i), fd);
				i = j;
			}
		}
	}
}

static void	child_program(char *file_name, char *limiter, int fd, char **env)
{
	char	*input;

	signal(SIGINT, handle_signal_h);
	while (1)
	{
		input = readline("heredoc > ");
		if (!input)
		{
			free(file_name);
			break ;
		}
		if (ft_strcmp(input, limiter))
		{
			free(input);
			free(file_name);
			break ;
		}
		expand_h(input, env, fd);
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	exit(0);
}

void	heredoc(char *limiter, bool *leave, unsigned int count, char **env)
{
	int		fd;
	char	*file_name;
	pid_t	pid;
	int		status;

	file_name = heredoc_name(count);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
		child_program(file_name, limiter, fd, env);
	else
	{
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_signal);
		if (status / 256 == 130)
		{
			unlink(file_name);
			*leave = false;
		}
		free(file_name);
	}
}
