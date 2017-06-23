/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:30:55 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/23 23:27:01 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_del(char *buf, t_cmdl *cmdl)
{
	if (ft_strequ(buf, K_BCKSP) && cmdl->pos)
	{
		ft_strremchar(cmdl->cmdl, (size_t)(cmdl->pos - 1));
		// ICI
		if ((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col))
			tputs(tgetstr("le", NULL), 1, sh_putc);
		else
		{
			tputs(tgetstr("up", NULL), 1, sh_putc);
			ft_printf("\033[%dC", g_meta.ws.ws_col);
		}
		--(cmdl->pos);
		// ICI
		if (cmdl->pos && ((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col)))
			tputs(tgetstr("le", NULL), 1, sh_putc);
		else if (cmdl->pos)
		{
			tputs(tgetstr("up", NULL), 1, sh_putc);
			ft_printf("\033[%dC", g_meta.ws.ws_col);
		}
		print_cmdl(cmdl);
	}
	else if (ft_strequ(buf, K_DEL) && (cmdl->cmdl[cmdl->pos]))
	{
		ft_strremchar(cmdl->cmdl, (size_t)(cmdl->pos));
		// ICI
		if (cmdl->pos && ((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col)))
			tputs(tgetstr("le", NULL), 1, sh_putc);
		else if (cmdl->pos)
		{
			tputs(tgetstr("up", NULL), 1, sh_putc);
			ft_printf("\033[%dC", g_meta.ws.ws_col);
		}
		print_cmdl(cmdl);
	}
	return (1);
}
