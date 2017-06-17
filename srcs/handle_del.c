/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:30:55 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/17 17:33:08 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		handle_del(char *buf, size_t *pos, char *cmdl)
{
	if (ft_strequ(buf, K_BCKSP) && *pos)
	{
		if (!tc_go_up(*pos))
			ft_putstr("\033[1D");
		ft_strremchar(cmdl, *pos - 1);
		print_cmdl(cmdl, *pos);
		--(*pos);
	}
	else if (ft_strequ(buf, K_DEL) && *pos < ft_strlen(cmdl))
	{
		ft_strremchar(cmdl, *pos);
		if (*pos)
		{
			tputs(tgetstr("sc", NULL), 1, sh_putc); //save cursor position
			ft_putstr("\033[1D"); // deplace le curseur a gauche
			tputs(tgetstr("ce", NULL), 1, sh_putc); //efface tout a droite du curseur
			ft_printf("%s", *pos ? (cmdl + *pos - 1) : cmdl);
			tputs(tgetstr("rc", NULL), 1, sh_putc); //restore cursor position
		}
		else
			print_cmdl(cmdl, *pos);
	}
	return (1);
}
