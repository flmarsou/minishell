/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2025/01/24 12:19:58 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	g_exit_status = 0;

#define _RESET "\001\e[0m\002"
#define _COLOR "\001\e[1m\e[38;2;255;165;0m\002"

static char **alloc_envp(char **envp)
{
	unsigned int	i;
	char			**env;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	env[i] = NULL;
	i = 0;
	while (envp[i])
	{
		env[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	main_loop(t_lexer *lexer, t_parser *parser, char ***env,
		t_redir *redir)
{
	char			*buffer;
	unsigned int	groups;
	(void)redir;

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
		if (parsing(lexer, &parser, *env, &groups))
		{
			exec(parser, groups, env, redir);
			free_parser(parser, groups);
		}
		free_lexer(lexer);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer		lexer;
	t_parser	parser;
	t_redir		redir;
	char		**env;
	(void)argc;
	(void)argv;

	env = alloc_envp(envp);
	signal(SIGINT, handle_signal);
	signal(SIGKILL, SIG_IGN);
	main_loop(&lexer, &parser, &env, &redir);
	rl_clear_history();
	write(STDOUT, "Exiting...\n", 11);
	free_env(&env);
	return (0);
}
