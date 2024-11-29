/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/29 15:02:04 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Debugger (REMOVE BEFORE PUSH !!)
static void	print_lexer(t_lexer lexer)
{
	const char		*tokens[] = {"Separator", "Command", "Single Quote",
		"Double Quote", "Pipe", "Input Redirect", "Output Redirect",
		"Heredoc", "Append Redirect", "Dollar"};
	unsigned int	i;

	i = 0;
	if (lexer.str[i])
	{
		fprintf(stderr, "\e[34m========== L E X E R ==========\e[0m\n");
		while (lexer.str[i])
		{
			fprintf(stderr, "String: \"\e[32m%s\e[0m\" Token: \e[32m%s\e[0m\n",
				lexer.str[i], tokens[lexer.token[i]]);
			i++;
		}
	}
}

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
	char		*buffer;
	t_environ	*environ;
	t_lexer		lexer;
	t_parser	parser;

	signal(SIGINT, handle_signal);
	init_struct(&environ, &lexer);
	while (true)
	{
		buffer = readline("Nanashell > ");
		if (!buffer || ft_strncmp(buffer, "exit", 4))
			break ;
		if (buffer)
			add_history(buffer);
		tokenizer(buffer, &lexer);
		print_lexer(lexer);
		parsing(lexer, &parser, *environ);
		free_all(buffer, &lexer);
	}
	free_all(buffer, &lexer);
	ft_lstfree(environ);
	rl_clear_history();
	write(STDOUT, "Exiting...\n", 11);
	return (0);
}
