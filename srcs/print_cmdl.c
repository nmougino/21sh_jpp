/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:36:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/05 08:14:09 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_putstr(t_cmdl *cmdl)
{
	char	*str;
	int		pos;

	pos = cmdl->pos;
	str = cmdl->cmdl + (pos ? pos - 1 : 0);
	while (*str)
	{
		write(1, str++, 1);
		if (!((*(str - 1) != '\n') && ((pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col))))
			tputs(tgetstr("sf", NULL), 1, sh_putc);
		++pos;
		tputs(tgetstr("ce", NULL), 1, sh_putc);
	}
}

/*
** Restaure la position du curseur decalee de 1 vers la droite.
*/

void	sh_restaure_cursor(int i, t_cmdl *cmdl)
{
	if (!i)
		tputs(tgetstr("ce", NULL), 1, sh_putc);
	while (i)
	{
		sh_go_up(cmdl, cmdl->pos + i);
		--i;
	}
}

void	print_cmdl(t_cmdl *cmdl)
{
	int	i;

	i = (int)(ft_strlen(cmdl->cmdl + cmdl->pos));
	sh_putstr(cmdl);
	sh_restaure_cursor(i, cmdl);
}
