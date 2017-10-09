/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 23:03:24 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/08 11:57:46 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

static int	get_hd_line(t_cmdl *cmdl)
{
	t_termios	tcap;
	t_termios	tcsave;

	g_meta.edmod = terminit(&tcap, &tcsave);
	g_meta.gcmdl_f = g_meta.edmod ? get_cmdl_loop : get_cmdl_notc;
	g_meta.gcmdl_f(cmdl);
	if (cmdl->cmdl)
		handle_back_slash(cmdl);
	if (g_meta.edmod && tcsetattr(0, TCSADRAIN, &tcsave) == -1)
		exit(tc_err_print(ERR_TCSETATTR_FAIL, 0) - 1);
	if (HISTO.is_in)
		history_exit(cmdl);
	else if (cmdl->cmdl)
		history_add(cmdl->cmdl);
	if (!cmdl->cmdl)
		return (0);
	return (1);
}

static void	get_hd_content(char **save, char *delem)
{
	t_cmdl	cmdl;
	int		live;

	live = 1;
	cmdl.cmdl = NULL;
	cmdl.pos = 0;
	g_meta.prompt_save = g_meta.prompt;
	g_meta.prompt = "heredoc> ";
	while (live)
	{
		if (!(live = get_hd_line(&cmdl)))
			live = 0;
		else if (cmdl.cmdl && !ft_strcmp(cmdl.cmdl, delem))
			live = 0;
		else
		{
			if (*save && **save)
				ft_stradd(save, "\n");
			ft_stradd(save, cmdl.cmdl);
		}
		sh_cmdl_init(&cmdl);
	}
	g_meta.prompt = g_meta.prompt_save;
}

void		handle_heredoc(char **dest)
{
	char	*save;
	int		i;

	save = ft_strdup("");
	get_hd_content(&save, *dest);
	if (save && *save)
		ft_stradd(&save, "\n");
	free(*dest);
	*dest = save;
}
