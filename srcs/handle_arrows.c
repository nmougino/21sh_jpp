/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:31:32 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/17 20:00:54 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		handle_arrows(char *buf, size_t *pos, char *cmdl)
{
	extern t_meta	g_meta;

	if (ft_strequ(buf, K_UP_A))
		return (1);
	else if (ft_strequ(buf, K_DO_A))
		return (1);
	if (ft_strequ(buf, K_RI_A) && *pos < ft_strlen(cmdl))
	{
		if (!tc_go_do(*pos))
			ft_putstr("\033[1C");
		*pos += (*pos < ft_strlen(cmdl)) ? 1 : 0;
		ft_dprintf(g_meta.fd, "right %zu / %d\n", *pos + ft_strlen(g_meta.prompt), g_meta.ws.ws_col);
	}
	else if (ft_strequ(buf, K_LE_A) && *pos)
	{
		if (!tc_go_up(*pos))
			ft_putstr("\033[1D");
		*pos -= *pos ? 1 : 0;
		ft_dprintf(g_meta.fd, "left %zu / %d\n", *pos + ft_strlen(g_meta.prompt), g_meta.ws.ws_col);
	}
	return (1);
}
