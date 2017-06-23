/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_alt_arrows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 23:28:41 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/23 23:29:20 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_alt_arrows(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_ALT_RI_A) && cmdl->cmdl[cmdl->pos])
	{
		if (!ft_strchr(" \n\t", cmdl->cmdl[cmdl->pos]))
			while (cmdl->cmdl[cmdl->pos] &&
				!ft_strchr(" \n\t", cmdl->cmdl[cmdl->pos]))
				handle_arrows(cmdl, K_RI_A);
		else
			while (cmdl->cmdl[cmdl->pos] &&
				ft_strchr(" \n\t", cmdl->cmdl[cmdl->pos]))
				handle_arrows(cmdl, K_RI_A);
	}
	else if (ft_strequ(buf, K_ALT_LE_A) && cmdl->pos)
	{
		if (!ft_strchr(" \n\t", cmdl->cmdl[cmdl->pos - 1]))
			while (cmdl->pos && !ft_strchr(" \n\t", cmdl->cmdl[cmdl->pos - 1]))
				handle_arrows(cmdl, K_LE_A);
		else
			while (cmdl->pos && ft_strchr(" \n\t", cmdl->cmdl[cmdl->pos - 1]))
				handle_arrows(cmdl, K_LE_A);
	}
	return (1);
}
