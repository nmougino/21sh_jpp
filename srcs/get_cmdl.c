/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:38:33 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/06 11:34:50 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** intercepte l'input, applique le bon traitement s'il y en a un
** renvoie 1 si l'input doit etre traite ou ignore
** renvoie 0 si l'input doit etre imprime
*/

static void		sh_putprompt(void)
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

static void		go_out(t_cmdl *cmdl)
{
	if (cmdl && cmdl->cmdl)
	{
		handle_end(cmdl);
		tputs(tgetstr("sf", NULL), 1, sh_putc);
	}
}

int				get_cmdl_loop(t_cmdl *cmdl)
{
	char		buf[6];

	ft_bzero(buf, 6);
	sh_putprompt();
	cmdl->cmdl = ft_strdup("");
	while (read(0, buf, 6))
	{
		if (buf[0] == 4)
		{
			sh_cmdl_init(cmdl);
			break ;
		}
		else if (buf[0] == 10)
			break ;
		else if (!handle_action(cmdl, buf))
		{
			ft_strinschar(&(cmdl->cmdl), (size_t)(cmdl->pos), buf[0]);
			(cmdl->pos)++;
			print_cmdl(cmdl);
		}
		ft_bzero(buf, 6);
	}
	go_out(cmdl);
	return (cmdl->cmdl ? 1 : 0);
}

int				get_cmdl(t_cmdl *cmdl)
{
	t_termios	tcap;
	t_termios	save;

	terminit(&tcap, &save);
	get_cmdl_loop(cmdl);
	if (cmdl->cmdl)
		handle_quotes(cmdl);
	if (tcsetattr(0, TCSADRAIN, &save) == -1)
		exit(tc_err_print(ERR_TCSETATTR_FAIL, 0));
	if (!cmdl->cmdl)
		return (0);
	history_add(cmdl->cmdl);
	if (HISTO.is_in)
		history_exit(cmdl);
	return (1);
}
