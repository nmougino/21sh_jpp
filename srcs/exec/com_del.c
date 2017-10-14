/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 18:48:03 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/14 21:43:08 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_strdel(&(com->heredoc)); very weeeeird
*/

void	com_del(t_com *com)
{
	if (com->fd[0] != 0)
		close(com->fd[0]);
	if (com->fd[1] != 1)
		close(com->fd[1]);
	if (com->fd[2] != 2)
		close(com->fd[2]);
	ft_strdel(&(com->cmd_path));
	ft_arrdel((void***)&(com->cmd_args));
}
