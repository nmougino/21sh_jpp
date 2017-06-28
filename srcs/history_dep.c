/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_dep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 20:58:17 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/27 22:10:09 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta;

void			history_add(char *new)
{
	ft_dlstadd(&(g_meta.history.lst), ft_dlstnew(new, ft_strlen(new) + 1));
}

static void		erase_cmdl(t_cmdl *cmdl)
{
	while (cmdl->cmdl[cmdl->pos])
		handle_arrows(cmdl, K_RI_A);
	while (cmdl->pos)
	{
		tputs(tgetstr("ce", NULL), 1, sh_putc);
		handle_arrows(cmdl, K_LE_A);
	}
}

static void		impose_history(t_dlist *cur, t_cmdl *cmdl)
{
	erase_cmdl(cmdl);
	(void)cur;
	g_meta.history.save = ft_memcpy(g_meta.history.save, cmdl, )
}

static void			history_do(t_cmdl *cmdl)
{
	(void)cmdl;
}

static void			history_up(t_cmdl *cmdl)
{
	if (g_meta.history.is_in)
	{

	}
	else
	{
		g_meta.history.is_in = 1;
		g_meta.history.cur = g_meta.history.lst;

		impose_history(g_meta.history.cur, cmdl);
	}
}

int				history_move(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_UP_A))
		history_up(cmdl);
	else if (ft_strequ(buf, K_DO_A))
		history_do(cmdl);
	return (1);
}
