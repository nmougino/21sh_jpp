/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_back_slash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 21:12:20 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/11 21:58:22 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	merge_cmdl(t_cmdl *tmp, t_cmdl *cmdl)
{
	if (tmp->cmdl)
	{
		if (!cmdl->cmdl)
			cmdl->cmdl = ft_strdup(tmp->cmdl);
		else
			ft_stradd(&(cmdl->cmdl), tmp->cmdl);
		ft_strdel(&(tmp->cmdl));
		tmp->pos = 0;
	}
}

void		handle_back_slash(t_cmdl *cmdl)
{
	char	*tmp;
	t_cmdl	tcmdl;

	tcmdl.cmdl = NULL;
	tcmdl.pos = 0;
	while (ft_strlen(cmdl->cmdl) &&
		cmdl->cmdl[ft_strlen(cmdl->cmdl) - 1] == '\\' &&
		!cmdl->cmdl[ft_strlen(cmdl->cmdl)])
	{
		tmp = ft_strndup(cmdl->cmdl, ft_strlen(cmdl->cmdl) - 1);
		ft_strdel(&cmdl->cmdl);
		cmdl->cmdl = tmp;
		g_meta.prompt = "> ";
		g_meta.gcmdl_f(&tcmdl);
		g_meta.prompt = g_meta.prompt_save;
		if (!tcmdl.cmdl)
		{
			sh_cmdl_init(cmdl);
			break ;
		}
		merge_cmdl(&tcmdl, cmdl);
		if (cmdl->cmdl)
			handle_quotes(cmdl);
	}
}
