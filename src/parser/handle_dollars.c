/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:13:08 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/10 09:01:41 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dollar_heredoc(t_lexer *lexer, unsigned int *i)
{
	(*i)++;
	while (lexer->str[*i] && lexer->token[*i] == SEPARATOR)
		(*i)++;
	if (lexer->str[*i] && lexer->token[*i] == DOLLAR)
		lexer->token[*i] = WORD;
}

static void	handle_dollar_digit(t_lexer *lexer, unsigned int *i)
{
	char	*buffer;

	lexer->token[*i] = NA_VALUE;
	(*i)++;
	buffer = ft_strdup(lexer->str[*i] + 1);
	free(lexer->str[*i]);
	lexer->str[*i] = buffer;
}

static void	handle_dollar_exit(t_lexer *lexer, unsigned int *i)
{
	char	*exit_status;
	char	*buffer;

	lexer->token[*i] = NA_VALUE;
	(*i)++;
	exit_status = ft_itoa(lexer->exit_status);
	buffer = ft_strdup(lexer->str[*i]);
	free(lexer->str[*i]);
	lexer->str[*i] = ft_strjoin(exit_status, buffer + 1);
	free(exit_status);
	free(buffer);
}

static void	handle_dollar_word(t_lexer *lexer, unsigned int *i, char **env)
{
	char	*var;

	lexer->token[*i] = NA_VALUE;
	(*i)++;
	var = find_in_env(lexer->str[*i], env);
	if (var)
	{
		free(lexer->str[*i]);
		lexer->str[*i] = malloc(sizeof(char) * (ft_strlen(var) + 1));
		ft_strcpy(lexer->str[*i], var);
	}
	else
		lexer->token[*i] = NA_VALUE;
}

void	handle_dollars(t_lexer *lexer, char **env)
{
	unsigned int	i;

	i = 0;
	while (lexer->str[i] && lexer->str[i + 1])
	{
		if (lexer->token[i] == HEREDOC)
			handle_dollar_heredoc(lexer, &i);
		else if (lexer->token[i] == DOLLAR && (lexer->token[i + 1] == WORD
				&& ft_isdigit(lexer->str[i + 1][0])))
			handle_dollar_digit(lexer, &i);
		else if (lexer->token[i] == DOLLAR && (lexer->token[i + 1] != WORD
				|| lexer->str[i + 1][0] == ' '))
			lexer->token[i] = WORD;
		else if (lexer->token[i] == DOLLAR && lexer->token[i + 1] == WORD
			&& lexer->str[i + 1][0] == '?')
			handle_dollar_exit(lexer, &i);
		else if (lexer->token[i] == DOLLAR && lexer->token[i + 1] == WORD)
			handle_dollar_word(lexer, &i, env);
		i++;
	}
	if (lexer->str[i] && lexer->token[i] == DOLLAR)
		lexer->token[i] = WORD;
}
