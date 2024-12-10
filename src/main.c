/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/10 13:01:36 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define _RESET	"\001\e[0m\002"
#define _COLOR	"\001\e[1m\e[38;2;255;165;0m\002"

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	free_all(char *buffer, t_lexer *lexer)
{
	unsigned int	i;

	if (buffer)
		free(buffer);
	i = 0;
	while (lexer->str && lexer->str[i])
		free(lexer->str[i++]);
	free(lexer->str);
	free(lexer->token);
	lexer->str = NULL;
	lexer->token = NULL;
}

int	main(void)
{
	char			*buffer;
	t_environ		*environ;
	t_lexer			lexer;
	t_parser		parser;
	unsigned int	groups;

	signal(SIGINT, handle_signal);
	init_struct(&environ, &lexer);
	while (true)
	{
		buffer = readline(_COLOR"Nanashell > "_RESET);
		if (!buffer)
			break ;
		if (buffer)
			add_history(buffer);
		tokenizer(buffer, &lexer);
		parsing(&lexer, &parser, *environ, &groups);
		free_all(buffer, &lexer);
	}
	free_all(buffer, &lexer);
	ft_lstfree(environ);
	rl_clear_history();
	write(STDOUT, "Exiting...\n", 11);
	return (0);
}
