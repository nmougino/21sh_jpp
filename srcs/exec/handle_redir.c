/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:54:18 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/28 20:58:08 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		restore_redir(int *save)
{
	dup2(save[0], 0);
	dup2(save[1], 1);
	dup2(save[2], 2);
	close(save[0]);
	close(save[1]);
	close(save[2]);
}

void		handle_redir(t_com *com, int *save)
{
	if (save)
	{
		save[0] = dup(0);
		save[1] = dup(1);
		save[2] = dup(2);
	}
	if (com)
	{
		dup2(com->fd[0], 0);
		dup2(com->fd[1], 1);
		dup2(com->fd[2], 2);
		if (com->to_close[0])
			close(0);
		if (com->to_close[1])
			close(1);
		if (com->to_close[2])
			close(2);
	}
}
