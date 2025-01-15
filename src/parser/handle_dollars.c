/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:13:08 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/15 15:27:51 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_in_env(char *var, char **envp)
{
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) && envp[i][len] == '=')
			return (envp[i] + ft_strlen(var) + 1);
		i++;
	}
	return (NULL);
}

static void	handle_dollar_exit(t_lexer *lexer, unsigned int *i)
{
	char	*exit_status;
	char	*buffer;

	lexer->token[*i] = NA_VALUE;
	(*i)++;
	exit_status = ft_itoa(g_exit_status);
	buffer = ft_strdup(lexer->str[*i]);
	free(lexer->str[*i]);
	lexer->str[*i] = ft_strjoin(exit_status, buffer + 1);
	free(exit_status);
	free(buffer);
}

static void	handle_dollar_word(t_lexer *lexer, unsigned int *i, char **envp)
{
	char	*var;

	lexer->token[*i] = NA_VALUE;
	(*i)++;
	var = find_in_env(lexer->str[*i], envp);
	if (var)
	{
		free(lexer->str[*i]);
		lexer->str[*i] = malloc(sizeof(char) * (ft_strlen(var) + 1));
		ft_strcpy(lexer->str[*i], var);
	}
	else
		lexer->token[*i] = NA_VALUE;
}

void	handle_dollars(t_lexer *lexer, char **envp)
{
	unsigned int	i;

	i = 0;
	while (lexer->str[i] && lexer->str[i + 1])
	{
		if (lexer->token[i] == HEREDOC)
		{
			i++;
			while (lexer->str[i] && lexer->token[i] == SEPARATOR)
				i++;
			if (lexer->str[i] && lexer->token[i] == DOLLAR)
				lexer->token[i] = WORD;
		}
		else if (lexer->token[i] == DOLLAR && lexer->token[i + 1] != WORD)
			lexer->token[i] = WORD;
		else if (lexer->token[i] == DOLLAR && lexer->token[i + 1] == WORD
			&& lexer->str[i + 1][0] == '?')
			handle_dollar_exit(lexer, &i);
		else if (lexer->token[i] == DOLLAR && lexer->token[i + 1] == WORD)
			handle_dollar_word(lexer, &i, envp);
		i++;
	}
	if (lexer->str[i] && lexer->token[i] == DOLLAR)
		lexer->token[i] = WORD;
}
