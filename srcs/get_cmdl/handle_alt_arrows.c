/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_alt_arrows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 23:28:41 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/06 10:41:14 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_alt_ri(t_cmdl *cmdl)
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

static void	handle_alt_le(t_cmdl *cmdl)
{
	if (!ft_strchr(" \n\t", cmdl->cmdl[cmdl->pos - 1]))
		while (cmdl->pos && !ft_strchr(" \n\t", cmdl->cmdl[cmdl->pos - 1]))
			handle_arrows(cmdl, K_LE_A);
	else
		while (cmdl->pos && ft_strchr(" \n\t", cmdl->cmdl[cmdl->pos - 1]))
			handle_arrows(cmdl, K_LE_A);
}

static void	handle_alt_up(t_cmdl *cmdl)
{
	int i;

	i = g_meta.ws.ws_col;
	if ((cmdl->pos + (int)ft_strlen(g_meta.prompt) > g_meta.ws.ws_col)
		&& ((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % g_meta.ws.ws_col
		> (int)ft_strlen(g_meta.prompt)))
		while (i--)
			handle_arrows(cmdl, K_LE_A);
}

static void	handle_alt_do(t_cmdl *cmdl)
{
	int i;

	i = g_meta.ws.ws_col;
	if (ft_strlen(cmdl->cmdl + cmdl->pos) >= g_meta.ws.ws_col)
		while (i--)
			handle_arrows(cmdl, K_RI_A);
}

int			handle_alt_arrows(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_ALT_RI_A) && cmdl->cmdl[cmdl->pos])
		handle_alt_ri(cmdl);
	else if (ft_strequ(buf, K_ALT_LE_A) && cmdl->pos)
		handle_alt_le(cmdl);
	else if (ft_strequ(buf, K_ALT_UP_A))
		handle_alt_up(cmdl);
	else if (ft_strequ(buf, K_ALT_DO_A))
		handle_alt_do(cmdl);
	return (1);
}
