/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_home_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 23:27:26 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/23 23:27:43 by nmougino         ###   ########.fr       */
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
		// ICI
		if ((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col))
			ft_printf("\033[1C");
		else
			tputs(tgetstr("sf", NULL), 1, sh_putc);
	}
	return (1);
}
