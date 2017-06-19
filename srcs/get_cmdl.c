/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:38:33 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/19 11:51:52 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta; //penser a supprimer

/*
** intercepte l'input, applique le bon traitement s'il y en a un
** renvoie 1 si l'input doit etre traite ou ignore
** renvoie 0 si l'input doit etre imprime
*/
//
// static int		handle_input(char *buf, size_t *pos, char *cmdl)
// {
// 	if (ft_strequ(buf, K_BCKSP) || ft_strequ(buf, K_DEL))
// 		return (handle_del(buf, pos, cmdl));
// 	else if (ft_strequ(buf, K_UP_A) || ft_strequ(buf, K_DO_A)
// 		|| ft_strequ(buf, K_RI_A) || ft_strequ(buf, K_LE_A))
// 		return (handle_arrows(buf, pos, cmdl));
// 	return (ft_isprint(buf[0]) ? 0 : 1);
// }
//
// char	*get_cmdl(void)
// {
// 	extern t_meta	g_meta;
// 	char			*cmdl; // ligne de commande
// 	char			buf[6]; // buffer de lecture des inputs
// 	size_t			pos; // position du curseur dans l'ecriture de la ligne de commande
//
// 	pos = 0;
// 	cmdl = ft_strdup("");
// 	ft_bzero(buf, 6);
// 	ft_putstr(g_meta.prompt);
// 	while (1)
// 	{
// 		read(0, buf, 6);
// 		metainit();
// 		if (buf[0] == 4)
// 		{
// 			ft_memdel((void **)&cmdl);
// 			break;
// 		}
// 		else if (buf[0] == 10)
// 			return (cmdl);
// 		else if (!handle_input(buf, &pos, cmdl))
// 		{
// 			ft_strinschar(&cmdl, pos++, buf[0]);
// 			// tc_go_do(pos);
// 			print_cmdl(cmdl, pos);
// 			//ft_putstr("\033[1C");
// 		}
// 		ft_bzero(buf, 6);
// 	}
// 	free(cmdl);
// 	return (NULL);
// }

static void	new_print_cmdl(t_cmdl *cmdl)
{
	size_t	i;

	i = ft_strlen(cmdl->cmdl + cmdl->pos - 1);
	ft_putstr(cmdl->cmdl + cmdl->pos - 1);
	if (cmdl->cmdl[cmdl->pos])
	{
		while (i)
		{
			if (!(cmdl->pos + (int)ft_strlen(g_meta.prompt) % (g_meta.ws.ws_col + 1)))
			{
				tputs(tgetstr("up", NULL), 1, sh_putc);
				ft_printf("\033[%dC", g_meta.ws.ws_col);
			}
			else
				tputs(tgetstr("le", NULL), 1, sh_putc);
			--i;
		}
	}
}

static int	new_handle_arrows(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_RI_A))
	{
		if (cmdl->cmdl[cmdl->pos])
		{
			write(1, cmdl->cmdl + cmdl->pos, 1);
			(cmdl->pos)++;
		}
	}
	else if (ft_strequ(buf, K_LE_A))
	{
		if (cmdl->pos)
		{
			if (!(cmdl->pos + (int)ft_strlen(g_meta.prompt) % (g_meta.ws.ws_col + 1)))
			{
				tputs(tgetstr("up", NULL), 1, sh_putc);
				ft_printf("\033[%dC", g_meta.ws.ws_col);
			}
			else
				tputs(tgetstr("le", NULL), 1, sh_putc);
			(cmdl->pos)--;
		}
	}
	return (1);
}

static int	handle_action(t_cmdl *cmdl, char *buf)
{
	(void)buf;
	(void)cmdl;
	if (ft_strequ(buf, K_UP_A) || ft_strequ(buf, K_DO_A)
		|| ft_strequ(buf, K_RI_A) || ft_strequ(buf, K_LE_A))
		return (new_handle_arrows(cmdl, buf));
	return (0);
}

void		new_get_cmdl(t_cmdl *cmdl)
{
	char	buf[6];

	ft_bzero(buf, 6);
	ft_putstr(g_meta.prompt);
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
			ft_dprintf(g_meta.fd, "insersion :: |%c| pos = %d\n", buf[0], cmdl->pos);
			ft_strinschar(&(cmdl->cmdl), (size_t)(cmdl->pos), buf[0]);
			(cmdl->pos)++;
			new_print_cmdl(cmdl);
			// (cmdl->pos)++;
		}
	}
}
