/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:23:12 by flmarsou          #+#    #+#             */
/*   Updated: 2024/10/28 13:00:22 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(const unsigned int error)
{
	write(1, "\e[1;31m[x] - Error: ", 21);
	if (error == 1)
		write(1, "\e[1;97mAllocation Failed!\n\e[0m", 31);
	else if (error == 2)
		write(1, "\e[1;97mSignal Failed!\n\e[0m", 31);
	else
		write(1, "\e[1;97mGet a brain!\n\e[0m", 25);
	exit(1);
}
