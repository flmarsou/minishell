/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:00:15 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/24 15:20:55 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_name(void)
{
	static unsigned int	i = 1;
	char				*ret;
	char				*itoa;

	itoa = ft_itoa(i++);
	ret = ft_strjoin(".heredoc_", itoa);
	free(itoa);
	return (ret);
}

int	heredoc(char *limiter)
{
	int		fd;
	char	*input;

	fd = open(heredoc_name(), O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		input = readline("heredoc > ");
		if (ft_strcmp(input, limiter))
		{
			free(input);
			break ;
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	return (fd);
}
