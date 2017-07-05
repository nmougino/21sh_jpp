/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:34:57 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/05 06:21:32 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
------------------

TERMCAPS:::

reste::	copier coller

------------------
*/

/*
** penser a remplacer les ansi escape sequences par des termcap
** ajouter fonction e check des termcaps pour decider de leur activation
** creer un mode de get_cmdl minishell
*/

t_meta	g_meta;

void	sh_cmdl_init(t_cmdl *cmdl)
{
	if (cmdl->cmdl)
		ft_strdel(&(cmdl->cmdl));
	cmdl->pos = 0;
}

int	main(int ac, char **av, char **env)
{
	t_cmdl		cmdl;
	(void)ac;
	(void)av;
	(void)env;

	cmdl.cmdl = NULL;
	cmdl.pos = 0;
	metainit();
	while (get_cmdl(&cmdl))
		sh_cmdl_init(&cmdl);
	destroy_history();
	close(g_meta.fd);
	free(g_meta.save);
	return (0);
}
