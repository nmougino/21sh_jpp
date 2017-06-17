/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:36:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/17 19:28:29 by nmougino         ###   ########.fr       */
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

	while (--src)
	{
		ft_dprintf(g_meta.fd, "restauration iteration %d\n", src + 1);
		if (!tc_go_up(src + pos))
			tputs(tgetstr("le", NULL), 1, sh_putc); // move left
	}
}

static size_t	sh_put_end(char *cmdl, size_t pos)
{
	size_t	i;

	i = 0;
	while (*cmdl)
	{
		write(1, cmdl, 1);
		++i;
		++cmdl;
		if (*cmdl)
			tc_go_do(pos + i);
	}
	return (i);
}

void			print_cmdl(char *cmdl, size_t pos)
{
	size_t	tmp;
	tputs(tgetstr("ce", NULL), 1, sh_putc); //efface tout a droite du curseur
	tmp = sh_put_end(pos ? (cmdl + pos - 1) : cmdl, pos);
	if (cmdl[pos])
		tc_cur_restauration(tmp, pos);
}
