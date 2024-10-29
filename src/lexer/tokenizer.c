/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */

/*   Created: 2024/10/21 13:20:02 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/24 10:32:24 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(unsigned char *input, t_lexer	*lexer)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	k = 0;
	lexer->str = malloc(sizeof(unsigned char *) * count_tokens(input) + 1);
	while (ft_isspace(input[i]))
		i++;
	while (input[i])
	{
		j = 0;
		if ((input[i] == '>' || input[i] == '<') && input[i + 1] == input[i]
			&& (input[i++] && input[i++]))
		{
			lexer->str[k] = malloc(sizeof(char) * 3);
			ft_strcpy(lexer->str[k], &input[i - 2], 2);
			lexer->str[k][2] = '\0';
			k++;
		}
		else if (ft_ismeta(input[i]) && !ft_isspace(input[i++]))
		{
			lexer->str[k] = malloc(sizeof(char) * 2);
			ft_strcpy(lexer->str[k], &input[i - 1], 1);
			lexer->str[k][1] = '\0';
			k++;
		}
		if (ft_isspace(input[i]))
		{
			lexer->str[k] = malloc(sizeof(char) * 2);
			ft_strcpy(lexer->str[k], &input[i], 1);
			lexer->str[k][1] = '\0';
			k++;
		}
		while (ft_isspace(input[i]))
			i++;
		if (ft_isprint(input[i]) && !ft_ismeta(input[i]) && !ft_isspace(input[i]))
		{
			while (ft_isprint(input[i + j]) && !ft_ismeta(input[i + j]) && !ft_isspace(input[i + j]))
				j++;
			lexer->str[k] = malloc(sizeof(char) * j);
			ft_strcpy(lexer->str[k], &input[i], j);
			lexer->str[k][j] = '\0';
			i += j;
			k++;
		}
	}
	lexer->str[k] = NULL;
}
