/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 10:47:17 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/08 23:23:43 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	erase_cmdl(t_cmdl *cmdl)
{
	handle_end(cmdl);
	while (cmdl->pos)
	{
		tputs(tgetstr("ce", NULL), 1, sh_putc);
		handle_arrows(cmdl, K_LE_A);
	}
	tputs(tgetstr("ce", NULL), 1, sh_putc);
}

void	histo_display(int fd)
{
	t_dlist	*cur;

	cur = HISTO.lst;
	while (cur)
	{
		ft_putendl_fd(cur->content, fd);
		cur = cur->next;
	}
}

void	histo_impose(t_cmdl *cmdl)
{
	erase_cmdl(cmdl);
	cmdl->cmdl = (char *)(HISTO.cur->content);
	cmdl->pos = 1;
	print_cmdl(cmdl);
	handle_end(cmdl);
}

void	histo_save(t_cmdl *cmdl)
{
	HISTO.save = ft_strdup(cmdl->cmdl);
	LOGS("save = |%s|", HISTO.save);
}
