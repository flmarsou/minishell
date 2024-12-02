/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:13:08 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/02 15:15:24 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_in_env(char *var, t_environ environ)
{
	while (environ.next)
	{
		if (ft_strncmp(environ.var, var, ft_strlen(var)))
			return (environ.var + ft_strlen(var) + 1);
		environ = *environ.next;
	}
	return ("\n");
}

void	handle_dollars(t_lexer *lexer, t_environ environ)
{
	return ;
}
