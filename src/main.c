/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:45:48 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/12 13:27:59 by anvacca          ###   ########.fr       */
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

static void	init_struct(t_environ **environ, t_lexer *lexer)
{
	t_environ		*head;
	t_environ		*current;
	unsigned int	i;

	lexer->str = NULL;
	lexer->token = NULL;
	head = ft_lstnew((unsigned char *)ENV[0]);
	current = head;
	i = 1;
	while (ENV[i])
	{
		current->next = ft_lstnew((unsigned char *)ENV[i]);
		current = current->next;
		i++;
	}
	*environ = head;
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

	signal(SIGINT, handle_signal);
	init_struct(&environ, &lexer);
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
	ft_lstfree(environ);
	rl_clear_history();
	write(STDOUT, "Exiting...\n", 11);
	return (0);
}
