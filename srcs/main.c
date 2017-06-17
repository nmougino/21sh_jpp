/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:34:57 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/17 19:06:17 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** penser a remplacer les ansi escape sequences par des termcap
** ajouter fonction e check des termcaps pour decider de leur activation
** creer un mode de get_cmdl minishell
*/

t_meta	g_meta;

int	main(int ac, char **av, char **env)
{
	char		*cmdl;
	t_termios	tcap;
	t_termios	save;
	(void)ac;
	(void)av;
	(void)env;

	terminit(&tcap, &save);
	metainit();
	g_meta.fd = open("./log.txt", O_WRONLY | O_TRUNC | O_CREAT);
	cmdl = get_cmdl();
	ft_printf(" :: %s\n", cmdl);
	if (tcsetattr(0, TCSADRAIN, &save) == -1)
		exit (tc_err_print(ERR_TCSETATTR_FAIL, 0));
	close(g_meta.fd);
	return (0);
}
