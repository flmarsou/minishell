/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:56:41 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/07 10:00:27 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_pipes_error(t_lexer lexer)
{
	unsigned int	i;
	bool			found_pipe;

	i = 0;
	found_pipe = false;
	while (lexer.str[i])
	{
		if (lexer.token[i] == PIPE)
		{
			if (found_pipe)
				return (ft_putstr_fd(SERR"Unexpected `|`\n", 2), false);
			found_pipe = true;
		}
		else if (lexer.token[i] == WORD)
			found_pipe = false;
		i++;
	}
	if (found_pipe)
		return (ft_putstr_fd(SERR"Unexpected `|`\n", 2), false);
	return (true);
}
