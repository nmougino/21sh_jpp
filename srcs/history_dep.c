/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_dep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 20:58:17 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/05 07:18:34 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta;

static void		history_add_forceps(void)
{
	t_dlist	*cur;

	cur = HISTO.lst;
	while (cur->next)
		cur = cur->next;
	if (cur->prev)
		cur->prev->next = NULL;
	ft_dlstdel(&cur, del_histo, TO_END);
}

void			history_add(char *new)
{
	if (!(new && *new))
		return ;
	if (ft_dlstlen(HISTO.lst) == HISTO.max)
		history_add_forceps();
	ft_dlstadd(&(HISTO.lst), ft_dlstnew(new, ft_strlen(new) + 1));
}

void			erase_cmdl(t_cmdl *cmdl)
{
	while (cmdl->cmdl[cmdl->pos])
		handle_arrows(cmdl, K_RI_A);
	while (cmdl->pos)
	{
		tputs(tgetstr("ce", NULL), 1, sh_putc);
		handle_arrows(cmdl, K_LE_A);
	}
	tputs(tgetstr("ce", NULL), 1, sh_putc);
}

void			histo_display(int fd)
{
	t_dlist	*cur;

	cur = HISTO.lst;
	while (cur)
	{
		ft_putendl_fd(cur->content, fd);
		cur = cur->next;
	}
}

static void		histo_impose(t_cmdl *cmdl)
{
	erase_cmdl(cmdl);
	cmdl->cmdl = (char *)(HISTO.cur->content);
	ft_dprintf(g_meta.fd, "Here cmdl = |%s|\n", cmdl->cmdl);
	cmdl->pos = 1;
	// tputs(tgetstr("le", NULL), 1, sh_putc); // ????
	print_cmdl(cmdl);
	handle_end(cmdl);
}

static void		histo_save(t_cmdl *cmdl)
{
	HISTO.save = malloc(sizeof(t_cmdl));
	ft_memcpy(HISTO.save, cmdl, sizeof(t_cmdl));
}

static void		histo_up_out(t_cmdl *cmdl)
{
	if (HISTO.lst)
	{
		HISTO.is_in = 1;
		HISTO.cur = HISTO.lst;
		histo_save(cmdl);
		histo_impose(cmdl);
	}
}

static void		histo_up_in(t_cmdl *cmdl)
{
	if (HISTO.cur->next)
	{
		HISTO.cur = HISTO.cur->next;
		histo_impose(cmdl);
	}
}

static void		histo_do_in(t_cmdl *cmdl)
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
		free(HISTO.save);
	}
}

int				history_move(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_UP_A) && !HISTO.is_in)
		histo_up_out(cmdl);
	else if (ft_strequ(buf, K_UP_A) && HISTO.is_in)
		histo_up_in(cmdl);
	else if (ft_strequ(buf, K_DO_A) && HISTO.is_in)
		histo_do_in(cmdl);
	return (1);
}

void 		history_exit(t_cmdl *cmdl)
{
	ft_dprintf(FD, "exit history\n");
	HISTO.is_in = 0;
	HISTO.cur = NULL;
	cmdl->cmdl = ft_strdup(cmdl->cmdl);
	free(HISTO.save);
}
