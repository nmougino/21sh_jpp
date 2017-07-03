/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_go_doup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 10:05:44 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/03 20:40:47 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta;

void	sh_go_do(t_cmdl *cmdl, int pos)
{
	if (((cmdl->cmdl)[pos] != '\n') && ((pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col)))
		ft_printf("\033[1C");
	else
		tputs(tgetstr("sf", NULL), 1, sh_putc);
}

void	sh_go_up(t_cmdl *cmdl, int pos)
{
	int	len;
	if (((cmdl->cmdl)[pos] != '\n') && ((pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col)))
		tputs(tgetstr("le", NULL), 1, sh_putc);
	else
	{
		// if (ft_getnbrline(cmdl->cmdl) > 1)
		// 	len = (int)ft_strlen(g_meta.prompt) + (int)(ft_getlinesize(ft_gotoline(cmdl->cmdl, ft_getnbrline(cmdl->cmdl) - ft_getnbrline(cmdl->cmdl + pos))));
		// else
			len = g_meta.ws.ws_col - 1;
		tputs(tgetstr("up", NULL), 1, sh_putc);
		ft_printf("\033[%dC", len);
	}
}
