/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:34:57 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/16 20:00:23 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	cmdl = get_cmdl();
	ft_printf(" :: %s\n", cmdl);
	if (tcsetattr(0, TCSADRAIN, &save) == -1)
		exit (tc_err_print(ERR_TCSETATTR_FAIL, 0));
	return (0);
}
