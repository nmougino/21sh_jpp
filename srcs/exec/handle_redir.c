/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:54:18 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/14 18:55:27 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		handle_redir(t_com *com)
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
