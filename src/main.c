/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/11 15:48:38 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_environ	*init_env(void)
{
	t_environ		*head;
	t_environ		*current;
	unsigned int	i;

	head = ft_lstnew(ENV[0]);
	current = head;
	i = 1;
	while (ENV[i])
	{
		current->next = ft_lstnew(ENV[i]);
		current = current->next;
		i++;
	}
	return (head);
}

static void	free_all(char *buffer, t_lexer *lexer, t_parser *parser)
{
	unsigned int	i;

	if (buffer)
		free(buffer);
	i = 0;
	while (lexer->str && lexer->str[i])
		free(lexer->str[i++]);
	// i = 0;
	// while (parser->str && parser->str[i])
		// free(parser->str[i++]);
	free(lexer->str);
	free(lexer->token);
	// free(parser->str);
	// free(parser->token);
	lexer->str = NULL;
	lexer->token = NULL;
	// parser->str = NULL;
	// parser->token = NULL;
}

int	main(void)
{
	char		*buffer;
	t_environ	*environ;
	t_lexer		lexer;
	t_parser	parser;

	signal(SIGINT, handle_signal);
	environ = init_env();
	while (true)
	{
		buffer = readline("Nanashell > ");
		if (!buffer || ft_strncmp(buffer, "exit", 4))
			break ;
		if (buffer)
			add_history(buffer);
		tokenizer((unsigned char *)buffer, &lexer);
		ft_export(&environ, "CACA=pipi popo");
		ft_env(environ);
		free_all(buffer, &lexer, &parser);
	}
	free_all(buffer, &lexer, &parser);
	ft_lstfree(environ);
	rl_clear_history();
	write(STDOUT, "Exiting...\n", 11);
	return (0);
}
