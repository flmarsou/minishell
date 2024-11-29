/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:53:24 by flmarsou          #+#    #+#             */
/*   Updated: 2024/11/29 15:01:59 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Used by the ft_export builtin to add a new variable in the ENV.
t_environ	*lstadd_last_env(t_environ **environ, char *input)
{
	t_environ	*current;

	current = *environ;
	while (current && current->next)
	{
		current = current->next;
	}
	current->next = lstnew_env(input);
	return (current);
}

// Creates a new node for every line in the ENV.
t_environ	*lstnew_env(char *var)
{
	t_environ	*new;

	new = malloc(sizeof(t_environ));
	if (!new)
		ft_perror(1);
	new->var = var;
	new->next = NULL;
	return (new);
}

void	init_struct(t_environ **environ, t_lexer *lexer)
{
	t_environ		*head;
	t_environ		*current;
	unsigned int	i;

	lexer->str = NULL;
	lexer->token = NULL;
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
