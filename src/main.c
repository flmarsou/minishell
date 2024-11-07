/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/07 13:31:56 by flmarsou         ###   ########.fr       */
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
	lexer->str = NULL;
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
		free_all(buffer, &lexer);
	}
	free_all(buffer, &lexer);
	rl_clear_history();
	write(STDOUT, "Exiting...\n", 11);
	return (0);
}
