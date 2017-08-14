/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 17:16:09 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/14 18:24:06 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** This function WILL NOT fork in order to create a new process.
*/

void		exec_simple(t_list *lst)
{
	t_com	com;

	handle_redir(lst, &com);
	exit (0);
}
