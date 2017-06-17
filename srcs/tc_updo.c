/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_updo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:33:19 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/17 19:52:54 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** va a la fin de la ligne precedente si besoin est
*/

int	tc_go_up(size_t pos)
{
	extern t_meta	g_meta;

	if (!((pos + ft_strlen(g_meta.prompt)) % g_meta.ws.ws_col))
	{
		ft_dprintf(g_meta.fd, "goup active\n");
		tputs(tgetstr("up", NULL), 1, sh_putc);
		ft_printf("\033[%dC", g_meta.ws.ws_col);
		return (1);
	}
	return (0);
}

/*
** va au debut de la ligne suivante si besoin est
*/

int	tc_go_do(size_t pos)
{
	extern t_meta	g_meta;

	if (!((pos + ft_strlen(g_meta.prompt)) % g_meta.ws.ws_col))
	{
		// tputs(tgetstr("dl", NULL), 1, sh_putc); //descend le curseur d'une ligne (et va a gauche)
		// write(1, "\n", 1);
		ft_dprintf(g_meta.fd, "godo active\n");
		tputs(tgetstr("do", NULL), 1, sh_putc);
		// tputs(tgetstr("do", NULL), 1, sh_putc); //descend le curseur d'une ligne (et va a gauche)
		return (1);
	}
	return (0);
}
