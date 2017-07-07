/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_dep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 20:58:17 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/06 15:19:35 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	histo_up_out(t_cmdl *cmdl)
{
	if (HISTO.lst)
	{
		HISTO.cur = HISTO.lst;
		histo_save(cmdl);
		histo_impose(cmdl);
		HISTO.is_in = 1;
	}
}

static void	histo_up_in(t_cmdl *cmdl)
{
	if (HISTO.cur->next)
	{
		HISTO.cur = HISTO.cur->next;
		histo_impose(cmdl);
	}
}

static void	histo_do_in(t_cmdl *cmdl)
{
	int	tmp;

	if (HISTO.cur->prev)
	{
		HISTO.cur = HISTO.cur->prev;
		histo_impose(cmdl);
	}
	else
	{
		HISTO.cur = NULL;
		HISTO.is_in = 0;
		erase_cmdl(cmdl);
		ft_memcpy(cmdl, HISTO.save, sizeof(t_cmdl));
		tmp = cmdl->pos;
		cmdl->pos = 0;
		print_cmdl(cmdl);
		while (cmdl->pos != tmp)
			handle_arrows(cmdl, K_RI_A);
		if (HISTO.save)
			sh_cmdl_init(HISTO.save);
		if (HISTO.save)
			ft_memdel((void **)(&(HISTO.save)));
	}
}

int			history_move(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_UP_A) && !HISTO.is_in)
		histo_up_out(cmdl);
	else if (ft_strequ(buf, K_UP_A) && HISTO.is_in)
		histo_up_in(cmdl);
	else if (ft_strequ(buf, K_DO_A) && HISTO.is_in)
		histo_do_in(cmdl);
	return (1);
}

void		history_exit(t_cmdl *cmdl)
{
	HISTO.is_in = 0;
	HISTO.cur = NULL;
	if (cmdl->cmdl)
		cmdl->cmdl = ft_strdup(cmdl->cmdl);
	if (HISTO.save)
		sh_cmdl_init(HISTO.save);
	if (HISTO.save)
		ft_memdel((void **)(&(HISTO.save)));
}
