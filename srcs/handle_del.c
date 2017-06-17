/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:30:55 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/17 20:21:40 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		handle_del(char *buf, size_t *pos, char *cmdl)
{
	if (ft_strequ(buf, K_BCKSP) && *pos)
	{
		ft_strremchar(cmdl, *pos - 1);
		--(*pos);
		if (!tc_go_up(*pos))
		{
			ft_dprintf(g_meta.fd, "to the left\n");
			tputs(tgetstr("le", NULL), 1, sh_putc); // move left
			if (*pos)
				tputs(tgetstr("le", NULL), 1, sh_putc); // move left
		}
		print_cmdl(cmdl, *pos);
	}
	else if (ft_strequ(buf, K_DEL) && cmdl[*pos])
	{
		ft_strremchar(cmdl, *pos);
		if (*pos)
			tputs(tgetstr("le", NULL), 1, sh_putc); // move left
		print_cmdl(cmdl, *pos);
		if (!(*pos) && cmdl[*pos])
			tputs(tgetstr("le", NULL), 1, sh_putc); // move left
	}
	return (1);
}
