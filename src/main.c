/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/07 15:50:05 by flmarsou         ###   ########.fr       */
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

static void	free_all(char *buffer, t_lexer *lexer)
{
	unsigned int	i;

	i = 0;
	if (buffer)
		free(buffer);
	while (lexer->str && lexer->str[i])
		free(lexer->str[i++]);
	free(lexer->str);
	free(lexer->token);
	lexer->str = NULL;
	lexer->token = NULL;
}

int	main(void)
{
	char	*buffer;
	t_lexer	lexer;

	signal(SIGINT, handle_signal);
	while (true)
	{
		buffer = readline("Nanashell > ");
		if (!buffer || ft_strncmp(buffer, "exit", 4))
			break ;
		if (buffer)
			add_history(buffer);
		tokenizer((unsigned char *)buffer, &lexer);
		for (unsigned int i = 0; lexer.str[i]; i++)
			fprintf(stderr, "ID: %u Token: %d - \"%s\"\n", i, lexer.token[i], lexer.str[i]); // Debug
		fprintf(stderr, "\n");
		free_all(buffer, &lexer);
	}
	free_all(buffer, &lexer);
	rl_clear_history();
	write(STDOUT, "Exiting...\n", 11);
	return (0);
}
