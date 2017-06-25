/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_alt_arrows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 23:28:41 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/24 20:46:24 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_alt_arrows(t_cmdl *cmdl, char *buf)
{
	int i;

	i = g_meta.ws.ws_col;
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
	else if (ft_strequ(buf, K_ALT_UP_A))
	{
		if ((cmdl->pos + (int)ft_strlen(g_meta.prompt) > g_meta.ws.ws_col) && ((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % g_meta.ws.ws_col > (int)ft_strlen(g_meta.prompt)))
			while (i--)
				handle_arrows(cmdl, K_LE_A);
	}
	else if (ft_strequ(buf, K_ALT_DO_A))
	{
		if (ft_strlen(cmdl->cmdl + cmdl->pos) >= g_meta.ws.ws_col)
			while (i--)
				handle_arrows(cmdl, K_RI_A);
	}
	return (1);
}
