/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clodup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 19:08:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/22 18:02:31 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** THE finest utility for not-plombers...
*/

void	clodup(int *fd, int i)
{
	if (!fd)
		return ;
	if (i)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}
