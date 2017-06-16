/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:38:33 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/16 16:02:09 by nmougino         ###   ########.fr       */
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

static int		handle_arrows(char *buf, size_t *pos, char *cmdl)
{
	// if (ft_strequ(buf, K_UP_A))
	// 	return (1);
	// else if (ft_strequ(buf, K_DO_A))
	// 	return (1);
	if (ft_strequ(buf, K_RI_A) && *pos < ft_strlen(cmdl))
		*pos += *pos < ft_strlen(cmdl) ? 1 : 0;
	else if (ft_strequ(buf, K_LE_A))
		*pos -= *pos ? 1 : 0;
	return (1);
}

static int		handle_del(char *buf, size_t *pos, char *cmdl)
{
	if (ft_strequ(buf, K_BCKSP) && *pos)
	{
		ft_strremchar(cmdl, *pos - 1);
		--(*pos);
	}
	else if (ft_strequ(buf, K_DEL) && *pos < ft_strlen(cmdl))
		ft_strremchar(cmdl, *pos);
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

static int	print_cmdl(char *prompt, char *cmdl, int pos)
{
	tputs(tgetstr("cr", NULL), 1, sh_putc); //curseur debut de ligne
	ft_printf("\033[K%s%s", prompt, cmdl);
	// ft_printf("\033[K%7d>> %s", pos, cmdl);
	tputs(tgetstr("cr", NULL), 1, sh_putc); //curseur debut de ligne
	ft_printf("\033[%dC", pos + (int)ft_strlen(prompt)); //deplace le curseur vers la droite
	return (1);
}

char	*get_cmdl(char *prompt)
{
	char	*cmdl;
	char	buf[6];
	size_t	pos;

	pos = 0;
	cmdl = ft_strdup("");
	ft_bzero(buf, 6);
	while (print_cmdl(prompt, cmdl, (int)pos))
	{
		read(0, buf, 6);
		// ft_printf("%o %o %o %o %o %o\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
		if (buf[0] == 4)
		{
			ft_memdel((void **)&cmdl);
			break;
		}
		else if (buf[0] == 10)
			return (cmdl);
		else if (!handle_input(buf, &pos, cmdl))
			ft_strinschar(&cmdl, pos++, buf[0]);
		ft_bzero(buf, 6);
	}
	free(cmdl);
	return (NULL);
}
