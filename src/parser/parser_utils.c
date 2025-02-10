/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:59:13 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/10 09:40:04 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_token(t_lexer *lexer, unsigned int y, char **src)
{
	lexer->token[y] = WORD;
	free(lexer->str[y]);
	lexer->str[y] = *src;
}

char	*find_in_env(char *var, char **env)
{
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) && env[i][len] == '=')
			return (env[i] + ft_strlen(var) + 1);
		i++;
	}
	return (NULL);
}
