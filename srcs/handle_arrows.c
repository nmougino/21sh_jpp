/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:31:32 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/26 17:36:57 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_arrows(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_RI_A))
	{
		if (cmdl->cmdl[cmdl->pos])
		{
			(cmdl->pos)++;
			// ICI
			if ((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col))
				ft_printf("\033[1C");
			else
				tputs(tgetstr("sf", NULL), 1, sh_putc);
		}
	}
	else if (ft_strequ(buf, K_LE_A))
	{
		if (cmdl->pos)
		{
			// ICI
			if ((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col))
				tputs(tgetstr("le", NULL), 1, sh_putc);
			else
			{
				tputs(tgetstr("up", NULL), 1, sh_putc);
				ft_printf("\033[%dC", g_meta.ws.ws_col);
			}
			(cmdl->pos)--;
		}
	}
	return (1);
}
