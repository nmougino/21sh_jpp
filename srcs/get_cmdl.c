/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:38:33 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/25 19:32:45 by nmougino         ###   ########.fr       */
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
	// if (ft_strequ(buf, K_UP_A) || ft_strequ(buf, K_DO_A))
	// 	return (history_move(cmdl, buf));
	if (ft_strequ(buf, K_RI_A) || ft_strequ(buf, K_LE_A))
		return (handle_arrows(cmdl, buf));
	else if (ft_strequ(buf, K_BCKSP) || ft_strequ(buf, K_DEL))
		return (handle_del(buf, cmdl));
	else if (ft_strequ(buf, K_HOME))
		return (handle_home(cmdl));
	else if (ft_strequ(buf, K_END))
		return (handle_end(cmdl));
	else if (ft_strequ(buf, K_ALT_LE_A) || ft_strequ(buf, K_ALT_RI_A) ||
		ft_strequ(buf, K_ALT_UP_A) || ft_strequ(buf, K_ALT_DO_A))
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

static void	merge_cmdl(t_cmdl *tmp, t_cmdl *cmdl)
{
	if (!cmdl->cmdl)
		cmdl->cmdl = ft_strdup(tmp->cmdl);
	else
	{
		ft_stradd(&(cmdl->cmdl), "\n");
		ft_stradd(&(cmdl->cmdl), tmp->cmdl);
	}
	ft_strdel(&(tmp->cmdl));
	tmp->pos = 0;
}

static int	quotes_scan(t_cmdl *cmdl)
{
	int	q;
	int	i;

	i = -1;
	q = 0;
	while (cmdl->cmdl[++i])
	{
		if (!q && cmdl->cmdl[i] == '\'')
			q = 1;
		else if (!q && cmdl->cmdl[i] == '"')
			q = 2;
		else if (!q && cmdl->cmdl[i] == '|' && !(cmdl->cmdl[i + 1]))
			q = 3;
		else if (cmdl->cmdl[i] == '\'' && q == 1)
			q = 0;
		else if (cmdl->cmdl[i] == '"' && q == 2)
			q = 0;
	}
	if (q == 1)
		g_meta.prompt = "quote > ";
	else if (q == 2)
		g_meta.prompt = "dquote > ";
	else if (q == 3)
		g_meta.prompt = "pipe > ";
	return (q);
}

static void	get_cmdl_loop(t_cmdl *cmdl)
{
	char		buf[6];

	tputs(tgetstr("RA", NULL), 1, sh_putc);
	ft_bzero(buf, 6);
	sh_putprompt();
	cmdl->cmdl = ft_strdup("");
	while (read(0, buf, 6))
	{
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
	tputs(tgetstr("sf", NULL), 1, sh_putc);
	tputs(tgetstr("SA", NULL), 1, sh_putc);
}

void		get_cmdl(t_cmdl *cmdl)
{
	t_termios	tcap;
	t_termios	save;
	t_cmdl		tmp;

	tmp.cmdl = NULL;
	tmp.pos = 0;
	terminit(&tcap, &save);
	get_cmdl_loop(&tmp);
	merge_cmdl(&tmp, cmdl);
	while (quotes_scan(cmdl))
	{
		get_cmdl_loop(&tmp);
		merge_cmdl(&tmp, cmdl);
		g_meta.prompt = g_meta.prompt_save;
	}
	if (tcsetattr(0, TCSADRAIN, &save) == -1)
		exit (tc_err_print(ERR_TCSETATTR_FAIL, 0));
}
