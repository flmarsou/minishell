/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:00:15 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/29 12:57:01 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal_h(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
}

static char	*heredoc_name(unsigned int count)
{
	char				*ret;
	char				*itoa;

	itoa = ft_itoa(count);
	ret = ft_strjoin(".heredoc_", itoa);
	free(itoa);
	return (ret);
}

void	heredoc(char *limiter, bool *leave, unsigned int count)
{
	int		fd;
	char	*input;
	char	*file_name;
	pid_t	pid;
	int		status;

	file_name = heredoc_name(count);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
	{
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
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
			free(input);
		}
		close(fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_signal);
		if(status / 256 == 130)
		{
			unlink(file_name);
			*leave = false;
		}
		free(file_name);
	}
}
