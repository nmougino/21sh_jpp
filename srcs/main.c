/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:34:57 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/10 05:19:26 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
	toujours un probleme dans le retour historique d'une commande sur plusieurs lignes
	Ajouter la verification termcaps
*/

/*
** penser a remplacer les ansi escape sequences par des termcap
** ajouter fonction e check des termcaps pour decider de leur activation
** creer un mode de get_cmdl minishell
*/

/*
	double free en CTRL D en parcours d'historique
*/

t_meta	g_meta;

void	sh_cmdl_init(t_cmdl *cmdl)
{
	if (cmdl->cmdl && !HISTO.is_in)
		ft_strdel(&(cmdl->cmdl));
	cmdl->pos = 0;
}

int		main(int ac, char **av, char **env)
{
	t_cmdl	cmdl;
	char	**tokens;

	(void)ac;
	(void)av;
	(void)env;
	cmdl.cmdl = NULL;
	cmdl.pos = 0;
	metainit();
	while (true)
	{
		if (!get_cmdl(&cmdl))
			break;
		tokens = cmdl_treatment(&cmdl);
		ft_putstrarr(tokens);
		ft_arrdel((void **)tokens);
		sh_cmdl_init(&cmdl);
	}
	destroy_history();
	close(g_meta.fd);
	if (g_meta.clipbo)
		free(g_meta.clipbo);
	int i = 1;
	while (i == 1);
	return (0);
}
