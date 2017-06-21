/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:38:33 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/21 19:00:26 by nmougino         ###   ########.fr       */
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

/*
** Le depassement en fin de cmdl fonctionne
** attelle toi aux fleches, puis au del
*/

// static int	sh_godo(int pos)
// {
// 	if (!((pos + (int)ft_strlen(g_meta.prompt)
// 	+ ((pos + (int)ft_strlen(g_meta.prompt)) > (g_meta.ws.ws_col + 1)))
// 	% (g_meta.ws.ws_col + 1)))
// 	{
// 		tputs(tgetstr("sf", NULL), 1, sh_putc);
// 		return (0);
// 	}
// 	return (1);
// }

// static int	sh_goup(int pos)
// {
// 	if (!((pos + (int)ft_strlen(g_meta.prompt)
// 	+ ((pos + (int)ft_strlen(g_meta.prompt)) > g_meta.ws.ws_col))
// 	% (g_meta.ws.ws_col)))
// 	{
// 		tputs(tgetstr("up", NULL), 1, sh_putc);
// 		ft_printf("\033[%dC", g_meta.ws.ws_col);
// 		return (0);
// 	}
// 	return (1);
// }

// static int	sh_godo_arrow(int pos)
// {
// 	if ((int)ft_strlen(g_meta.prompt) + pos)
// }

static int	new_handle_arrows(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_RI_A))
	{
		if (cmdl->cmdl[cmdl->pos])
		{
			(cmdl->pos)++;
			if ((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col))
				ft_printf("\033[1C");
			else
				tputs(tgetstr("sf", NULL), 1, sh_putc);
		}
	}
	else if (ft_strequ(buf, K_LE_A))
	{
		if (cmdl->pos)
		{
			ft_dprintf(g_meta.fd, "left :: |%d| pos + prompt = %d\n", (cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col), cmdl->pos + (int)ft_strlen(g_meta.prompt));
			if ((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col))
				tputs(tgetstr("le", NULL), 1, sh_putc);
			else
			{
				tputs(tgetstr("up", NULL), 1, sh_putc);
				ft_printf("\033[%dC", g_meta.ws.ws_col);
			}
			(cmdl->pos)--;
		}
	}
	return (1);
}

static int	handle_action(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_UP_A) || ft_strequ(buf, K_DO_A)
		|| ft_strequ(buf, K_RI_A) || ft_strequ(buf, K_LE_A))
		return (new_handle_arrows(cmdl, buf));
	return (0);
}

static void	sh_putstr(t_cmdl *cmdl)
{
	char	*str;
	int		pos;

	str = cmdl->cmdl + cmdl->pos - 1;
	pos = cmdl->pos;
	while (*str)
	{
		write(1, str, 1);
		++str;
		if (!((pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col)))
			tputs(tgetstr("sf", NULL), 1, sh_putc);
		++pos;
		tputs(tgetstr("ce", NULL), 1, sh_putc);
	}
}

static void	new_print_cmdl(t_cmdl *cmdl)
{
	int	i;

	i = (int)(ft_strlen(cmdl->cmdl + cmdl->pos - 1)) - 1;
	sh_putstr(cmdl);
	/*
	**si tu n'es pas a la fin de la chaine, ca veut dire qu'en affichant
	**la chaine decalee, le curseur est toujours a la fin, il faut donc
	**restaurer sa position d'origine decalee de 1 vers la droite.
	*/
	if (cmdl->cmdl[cmdl->pos])
	{
		while (i > 0)
		{
			if (!((i + cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col + 1)))
			{
				// ft_dprintf(g_meta.fd, "pupup\n");
				tputs(tgetstr("up", NULL), 1, sh_putc);
				ft_printf("\033[%dC", g_meta.ws.ws_col - 1);
			}
			else
			{
				// ft_dprintf(g_meta.fd, "ramen a goch\n");
				tputs(tgetstr("le", NULL), 1, sh_putc);
			}
			--i;
		}
	}
}

void		new_get_cmdl(t_cmdl *cmdl)
{
	char	buf[6];

	tputs(tgetstr("RA", NULL), 1, sh_putc);
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
			// ft_dprintf(g_meta.fd, "insersion :: |%c| pos = %d\n", buf[0], cmdl->pos);
			ft_strinschar(&(cmdl->cmdl), (size_t)(cmdl->pos), buf[0]);
			(cmdl->pos)++;
			new_print_cmdl(cmdl);
			// if (!((cmdl->pos + (int)ft_strlen(g_meta.prompt)) % (g_meta.ws.ws_col)))
			// {
			// 	// tputs(tgetstr("dl", NULL), 1, sh_putc); //descend le curseur d'une ligne (et va a gauche)
			// 	// write(1, "\n", 1);
			// 	ft_dprintf(g_meta.fd, "godo active %zu %zu %zu\n", cmdl->pos, ft_strlen(g_meta.prompt), (size_t)(g_meta.ws.ws_col + 1));
			// 	tputs(tgetstr("sf", NULL), 1, sh_putc);
			// 	// tputs(tgetstr("do", NULL), 1, sh_putc); //descend le curseur d'une ligne (et va a gauche)
			// }

			// (cmdl->pos)++;
		}
	}
	tputs(tgetstr("SA", NULL), 1, sh_putc);
}
