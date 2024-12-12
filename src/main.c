/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/12/12 10:37:30 by flmarsou         ###   ########.fr       */
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

static void	init_env(t_environ **environ)
{
	t_environ		*head;
	t_environ		*current;
	unsigned int	i;

	head = lstnew_env(ENV[0]);
	current = head;
	i = 1;
	while (ENV[i])
	{
		current->next = lstnew_env(ENV[i]);
		current = current->next;
		i++;
	}
	*environ = head;
}

static void	main_loop(t_lexer *lexer, t_parser *parser, t_environ *environ)
{
	char			*buffer;
	unsigned int	groups;

	while (true)
	{
		buffer = readline(_COLOR"Nanashell > "_RESET);
		if (!buffer)
			break ;
		if (buffer)
			add_history(buffer);
		tokenizer(buffer, lexer);
		parsing(lexer, parser, *environ, &groups);
	}
}

int	main(void)
{
	t_environ		*environ;
	t_lexer			lexer;
	t_parser		parser;

	signal(SIGINT, handle_signal);
	init_env(&environ);
	main_loop(&lexer, &parser, environ);
	free_env(environ);
	rl_clear_history();
	write(STDOUT, "Exiting...\n", 11);
	return (0);
}
