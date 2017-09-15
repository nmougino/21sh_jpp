/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 23:03:24 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/14 20:18:26 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// static void	grab_hd_content(t_com *com)
// {
// 	char	*total;
// 	char	*cur;
//
// 	total = NULL;
// 	cur = NULL;
// 	while (cur && ft_strcmp(cur, com->heredoc))
// 	{
// 		if (hd_get_next_line(&cur) != 1)
// 			break ;
//
// 		ft_strdel(&cur);
// 	}
// 	if (ft_strcmp(cur, com->heredoc))
// }

void	handle_heredoc(t_com *com)
{
	t_cmdl	cmdl;
	t_cmdl	save;
	t_termios	tcap;
	t_termios	tcsave;

	if (!com->heredoc)
	{
		ft_printf("aboooort\n");
		return ;
	}
	cmdl.cmdl = NULL;
	cmdl.pos = 0;
	save = cmdl;
	g_meta.prompt_save = g_meta.prompt;
	g_meta.prompt = "> ";
	g_meta.edmod = terminit(&tcap, &tcsave);
	g_meta.gcmdl_f = g_meta.edmod ? get_cmdl_loop : get_cmdl_notc;
	g_meta.gcmdl_f(&cmdl);
	if (cmdl.cmdl)
		handle_back_slash(&cmdl);
	if (g_meta.edmod && tcsetattr(0, TCSADRAIN, &tcsave) == -1)
		exit(tc_err_print(ERR_TCSETATTR_FAIL, 0) - 1);
	if (HISTO.is_in)
		history_exit(&cmdl);
	else if (cmdl.cmdl)
		history_add(cmdl.cmdl);
	ft_printf("POUR UNE RAISON FOLLE, CA N'A PAS PLANTE!!!\n et voici THE contenu %s\n", cmdl.cmdl);
	g_meta.prompt = g_meta.prompt_save;
}
