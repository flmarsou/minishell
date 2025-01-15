/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/15 15:29:07 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	g_exit_status = 0;

#define _RESET "\001\e[0m\002"
#define _COLOR "\001\e[1m\e[38;2;255;165;0m\002"

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

static void	main_loop(t_lexer *lexer, t_parser *parser, char **envp,
		t_redir *redir)
{
	char			*buffer;
	unsigned int	groups;
	bool			parser_valid;

	while (true)
	{
		buffer = readline(_COLOR "Nanashell > "_RESET);
		if (!buffer)
			break ;
		if (buffer[0] == '\0')
		{
			free(buffer);
			continue ;
		}
		if (buffer)
			add_history(buffer);
		tokenizer(buffer, lexer);
		free(buffer);
		parser_valid = parsing(lexer, &parser, envp, &groups);
		free_lexer(lexer);
		if (parser_valid)
		{
			print_parser(parser, groups);
			free_parser(parser, groups);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer		lexer;
	t_parser	parser;
	t_redir		redir;
	(void)argc;
	(void)argv;

	signal(SIGINT, handle_signal);
	main_loop(&lexer, &parser, envp, &redir);
	rl_clear_history();
	write(STDOUT, "Exiting...\n", 11);
	return (0);
}
