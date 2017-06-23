/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:38:33 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/23 23:43:57 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta;

/*
** intercepte l'input, applique le bon traitement s'il y en a un
** renvoie 1 si l'input doit etre traite ou ignore
** renvoie 0 si l'input doit etre imprime
*/

static int	handle_action(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_UP_A) || ft_strequ(buf, K_DO_A)
		|| ft_strequ(buf, K_RI_A) || ft_strequ(buf, K_LE_A))
		return (handle_arrows(cmdl, buf));
	else if (ft_strequ(buf, K_BCKSP) || ft_strequ(buf, K_DEL))
		return (handle_del(buf, cmdl));
	else if (ft_strequ(buf, K_HOME))
		return (handle_home(cmdl));
	else if (ft_strequ(buf, K_END))
		return (handle_end(cmdl));
	else if (ft_strequ(buf, K_ALT_LE_A) || ft_strequ(buf, K_ALT_RI_A))
		return (handle_alt_arrows(cmdl, buf));
	return (0);
}

static void	sh_putprompt(void)
{
	char	*str;
	int		pos;

	pos = 0;
	str = g_meta.prompt;
	while (*str)
	{
		write(1, str, 1);
		++str;
		++pos;
		if (!(pos % (g_meta.ws.ws_col)))
			tputs(tgetstr("sf", NULL), 1, sh_putc);
		tputs(tgetstr("ce", NULL), 1, sh_putc);
	}
}

void		get_cmdl(t_cmdl *cmdl)
{
	char	buf[6];

	tputs(tgetstr("RA", NULL), 1, sh_putc);
	ft_bzero(buf, 6);
	sh_putprompt();
	cmdl->cmdl = ft_strdup("");
	while (1)
	{
		read(0, buf, 6);
		if (buf[0] == 4)
		{
			sh_cmdl_init(cmdl);
			break;
		}
		else if (buf[0] == 10)
			break;
		else if (!handle_action(cmdl, buf))
		{
			ft_strinschar(&(cmdl->cmdl), (size_t)(cmdl->pos), buf[0]);
			(cmdl->pos)++;
			print_cmdl(cmdl);
		}
		ft_bzero(buf, 6);
	}
	tputs(tgetstr("SA", NULL), 1, sh_putc);
}
