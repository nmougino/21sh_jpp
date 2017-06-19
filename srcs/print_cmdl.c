/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:36:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/18 21:02:21 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Restitue la position du curseur
** Alternative favorable a la sauvegarde de la position du curseur
** native des termcaps
*/

static void		tc_cur_restauration(size_t src, size_t pos)
{
	extern t_meta	g_meta;

	while (src--)
	{
		ft_dprintf(g_meta.fd, "ICI > %zu + %zu = %zu\n", src, pos, src + pos);
		if (!tc_go_up(src + pos))
			tputs(tgetstr("le", NULL), 1, sh_putc); // move left
		ft_dprintf(g_meta.fd, "LA\n");
	}
}

static void		sh_putstr_clear(char *cmdl, size_t pos)
{
	(void)pos;
	while (*cmdl)
	{
		ft_dprintf(g_meta.fd, "ICI\n");
		// tc_go_do(pos++);
		ft_dprintf(g_meta.fd, "la\n");
		write(1, cmdl++, 1);

	}
	tputs(tgetstr("ie", NULL), 1, sh_putc);
}

void			print_cmdl(char *cmdl, size_t pos)
{
	size_t	tmp;
	char	*tar;

	tar = pos ? (cmdl + pos - 1) : cmdl;
	tputs(tgetstr("ce", NULL), 1, sh_putc); //efface tout a droite du curseur
	sh_putstr_clear(tar, pos + 1);
	tmp = ft_strlen(tar) - 1;
	// if (cmdl[pos])
	// 	tc_cur_restauration(tmp);
	// else
	// 	ft_dprintf(g_meta.fd, " >  %d\n", tmp);
	if (tmp)
		tc_cur_restauration(tmp, pos);
}
