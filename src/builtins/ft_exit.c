/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:10:17 by flmarsou          #+#    #+#             */
/*   Updated: 2025/02/04 11:45:04 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **command, unsigned int nbr_of_cmd)
{
	(void)command;
	(void)nbr_of_cmd;
	printf("WIP\n");
	if (nbr_of_cmd > 1)
		exit(atoi(command[1]));
	exit(0);
}
