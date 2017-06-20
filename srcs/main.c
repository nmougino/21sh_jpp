/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:34:57 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/19 15:14:28 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** penser a remplacer les ansi escape sequences par des termcap
** ajouter fonction e check des termcaps pour decider de leur activation
** creer un mode de get_cmdl minishell
*/

t_meta	g_meta;

void	sh_cmdl_init(t_cmdl *cmdl)
{
	if (cmdl->cmdl)
		ft_memdel((void**)(&(cmdl->cmdl)));
	cmdl->pos = 0;
}

int	main(int ac, char **av, char **env)
{
	t_termios	tcap;
	t_termios	save;
	t_cmdl		cmdl;
	(void)ac;
	(void)av;
	(void)env;

	cmdl.cmdl = NULL;
	cmdl.pos = 0;
	terminit(&tcap, &save);
	metainit();
	g_meta.fd = open("./log.txt", O_WRONLY | O_TRUNC | O_CREAT);
	tputs(tgetstr("RA", NULL), 1, sh_putc);
	new_get_cmdl(&cmdl);
	ft_printf("\n :: %s\n", cmdl.cmdl);
	if (tcsetattr(0, TCSADRAIN, &save) == -1)
		exit (tc_err_print(ERR_TCSETATTR_FAIL, 0));
	close(g_meta.fd);
	sh_cmdl_init(&cmdl);
	return (0);
}
