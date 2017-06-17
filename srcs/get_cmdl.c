/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:38:33 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/17 13:23:31 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// 1 : trigguer une touche;
// 2 : convertir la touche en action;

static int		sh_putc(int c)
{
	write(1, &c, 1);
	return (1);
}

// static void		sh_put_end(size_t pos, char *cmdl)
// {
// 	extern t_meta	g_meta;
//
// 	while (*cmdl)
// 	{
// 		while (*cmdl && (int)(pos + ft_strlen(g_meta.prompt)) % g_meta.ws.ws_col)
// 		{
// 			ft_dprintf(2, "ici\n");
// 			write(1, cmdl, 1);
// 			++pos;
// 			++cmdl;
// 		}
// 		if (!((int)(pos + ft_strlen(g_meta.prompt)) % g_meta.ws.ws_col))
// 		{
// 			// ft_putstr("\033[1B");
// 			ft_dprintf(2, "fuck : %d %% %d = %d\n", (int)(pos + ft_strlen(g_meta.prompt)), g_meta.ws.ws_col, (int)(pos + ft_strlen(g_meta.prompt)) % g_meta.ws.ws_col);
// 			tputs(tgetstr("do", NULL), 1, sh_putc);
// 			// tputs(tgetstr("cr", NULL), 1, sh_putc);
// 			ft_putstr("\033[1G");
// 			if (*cmdl)
// 			{
// 				write(1, cmdl, 1);
// 				++pos;
// 				++cmdl;
// 			}
// 			else
// 				tputs(tgetstr("sc", NULL), 1, sh_putc); //save cursor position
// 		}
// 	}
// }

/*
** l'edition au cas ou la ligne depasse la taille maximale est bien chiante.
** il faut reconsiderer le deplacement des fleches.
** pos + prompt % largeur == 0 => monter et aller a droite ou descendre et aller a gauche selon l'action
**
** bien repenser la sauvegarde du curseur.
*/

// static int		print_cmdl(char *cmdl, size_t pos)
// {
// 	tputs(tgetstr("sc", NULL), 1, sh_putc); //save cursor position
// 	tputs(tgetstr("ce", NULL), 1, sh_putc); //efface tout a droite du curseur
// 	// sh_put_end(pos, pos ? (cmdl + pos - 1) : cmdl);
// 	ft_printf("%s", pos ? (cmdl + pos - 1) : cmdl);
// 	tputs(tgetstr("rc", NULL), 1, sh_putc); //restore cursor position
// 	return (1);
// }

/*
** 1 : save cursor position
**  -> effacer a droite du curseur
** 2 : afficher caractere par caractere a droite du curseur
** 3 : quand !((position + strlen(prompt)) % largeur du terminal)	=> incrementer compteur ligne
** 																	=> nouvelle ligne
**																		-> effacer toute la ligne
** 																	=> continuer d'afficher a partir de la
** 4 : une fois fini, restaurer la position initiale du curseur puis remonter du nombre de ligne comptee.
*/

static int		sh_put_end(char *cmdl, size_t pos)
{
	extern t_meta	g_meta;
	int				line;

	line = 0;
	pos += ft_strlen(g_meta.prompt);
	while (*cmdl)
	{
		write(1, cmdl, 1);
		++pos;
		++cmdl;
		if (!(pos % g_meta.ws.ws_col) && *cmdl)
		{
			++line;
			tputs(tgetstr("do", NULL), 1, sh_putc); //descend le curseur d'une ligne
			ft_printf("\033[%dD", g_meta.ws.ws_col - 1); //envoie le curseur a gauche
			tputs(tgetstr("ce", NULL), 1, sh_putc); //efface tout a droite du curseur
		}
	}
	return (line);
}

static void		print_cmdl(char *cmdl, size_t pos)
{
	int	line;

	tputs(tgetstr("sc", NULL), 1, sh_putc); //save cursor position
	tputs(tgetstr("ce", NULL), 1, sh_putc); //efface tout a droite du curseur
	line = sh_put_end(pos ? (cmdl + pos - 1) : cmdl, pos);
	tputs(tgetstr("rc", NULL), 1, sh_putc); //restore cursor position
	while (line--)
		tputs(tgetstr("up", NULL), 1, sh_putc); //rehause le curseur d'une ligne
}


static int		handle_arrows(char *buf, size_t *pos, char *cmdl)
{
	if (ft_strequ(buf, K_UP_A))
		return (1);
	else if (ft_strequ(buf, K_DO_A))
		return (1);
	if (ft_strequ(buf, K_RI_A) && *pos < ft_strlen(cmdl))
	{
		ft_putstr("\033[1C");
		*pos += (*pos < ft_strlen(cmdl)) ? 1 : 0;
	}
	else if (ft_strequ(buf, K_LE_A) && *pos)
	{
		ft_putstr("\033[1D");
		*pos -= *pos ? 1 : 0;
	}
	return (1);
}

static int		handle_del(char *buf, size_t *pos, char *cmdl)
{
	if (ft_strequ(buf, K_BCKSP) && *pos)
	{
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

/*
** intercepte l'input, applique le bon traitement s'il y en a un
** renvoie 1 si l'input doit etre traite ou ignore
** renvoie 0 si l'input doit etre imprime
*/

static int		handle_input(char *buf, size_t *pos, char *cmdl)
{
	if (ft_strequ(buf, K_BCKSP) || ft_strequ(buf, K_DEL))
		return (handle_del(buf, pos, cmdl));
	else if (ft_strequ(buf, K_UP_A) || ft_strequ(buf, K_DO_A)
		|| ft_strequ(buf, K_RI_A) || ft_strequ(buf, K_LE_A))
		return (handle_arrows(buf, pos, cmdl));
	return (ft_isprint(buf[0]) ? 0 : 1);
}

// si la cmdl depace la taille horizontale du terminal ca fait de la merde.
// corriger ca avec la deduction du nombre de ligne necessaire via un modulo

// static int	print_cmdl(char *prompt, char *cmdl, int pos, int line)
// {
// 	extern t_meta	g_meta;
//
// 	line += ft_strlen(cmdl) % g_meta.ws.ws_col;
// 	tputs(tgetstr("cr", NULL), 1, sh_putc); //curseur debut de ligne
// 	ft_printf("\033[K%s%s", prompt, cmdl);
// 	// ft_printf("\033[K%7d>> %s", pos, cmdl);
// 	tputs(tgetstr("cr", NULL), 1, sh_putc); //curseur debut de ligne
// 	ft_printf("\033[%dC", pos + (int)ft_strlen(prompt)); //deplace le curseur vers la droite
// 	return (1);
// }

char	*get_cmdl(void)
{
	extern t_meta	g_meta;
	char			*cmdl; // ligne de commande
	char			buf[6]; // buffer de lecture des inputs
	size_t			pos; // position du curseur dans l'ecriture de la ligne de commande

	pos = 0;
	cmdl = ft_strdup("");
	ft_bzero(buf, 6);
	ft_putstr(g_meta.prompt);
	while (1)
	{
		read(0, buf, 6);
		metainit();
		if (buf[0] == 4)
		{
			ft_memdel((void **)&cmdl);
			break;
		}
		else if (buf[0] == 10)
			return (cmdl);
		else if (!handle_input(buf, &pos, cmdl))
		{
			ft_strinschar(&cmdl, pos, buf[0]);
			if (!((pos + ft_strlen(g_meta.prompt) + 1) % g_meta.ws.ws_col))
			{
				tputs(tgetstr("do", NULL), 1, sh_putc); //descend le curseur d'une ligne
				ft_printf("\033[%dD", g_meta.ws.ws_col - 1); //envoie le curseur a gauche
			}
			print_cmdl(cmdl, ++pos);
			ft_putstr("\033[1C");
		}
		ft_bzero(buf, 6);
	}
	free(cmdl);
	return (NULL);
}

// else if (!handle_input(buf, &pos, cmdl))
// {
// 	ft_strinschar(&cmdl, pos++, buf[0]);
// 	print_cmdl(cmdl, pos);
// 	ft_putstr("\033[1C");
// }
