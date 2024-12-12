/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andi <andi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:53:50 by andi              #+#    #+#             */
/*   Updated: 2024/12/12 20:14:29 by andi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec(t_parser *parser, unsigned int *groups)
{
	//parser[0] = premier groupe etc
	// parser->redir.nbr_of_redirs = les redirections
	unsigned int i;
	int fd;
	int file;

	i = 0;
	while (i < groups)
	{
		heredoc(&parser[i]);
		if (parser[i]->redir.nbr_of_redirs - is_output_redir(&parser[i]) > 0)
			create_file(&parser[i])
		if (!is_builtins(&parser[i]))
		{
			
		}
		i++;
	}
}