/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_home_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 23:27:26 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/05 08:19:02 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_home(t_cmdl *cmdl)
{
	sh_restaure_cursor(cmdl->pos, cmdl);
	cmdl->pos = 0;
	return (1);
}

int	handle_end(t_cmdl *cmdl)
{
	while (cmdl->cmdl[cmdl->pos])
	{
		(cmdl->pos)++;
		sh_go_do(cmdl, cmdl->pos);
	}
	return (1);
}
