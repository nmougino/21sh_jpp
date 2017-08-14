/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 17:16:09 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/14 16:16:06 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	com_init(t_com *com)
{
	com->cmd_path = NULL;
	com->cmd_args = NULL;
	ft_bzero(&(com->fd), sizeof(int) * 3);
	ft_bzero(&(com->to_close), sizeof(int) * 3);
}

/*
** This function WILL NOT fork in order to create a new process.
*/

void		exec_simple(t_list *lst)
{
	t_com	com;

	com_init(&com);
	handle_redir(lst, &com);
	if (get_cmd_path(lst, &com) == -1)
		exit (-1);
	exit (0);
}
