/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:31:32 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/01 10:10:19 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta;

int	handle_arrows(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_RI_A) && cmdl->cmdl[cmdl->pos])
		sh_go_do(cmdl, ++(cmdl->pos));
	else if (ft_strequ(buf, K_LE_A) && cmdl->pos)
		sh_go_up(cmdl, cmdl->pos--);
	return (1);
}
