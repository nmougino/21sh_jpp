/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_alt_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 00:12:11 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/06 10:28:48 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta;

static void	handle_alt_k(t_cmdl *cmdl)
{
	int	tmp;

	if (!cmdl->cmdl[cmdl->pos])
		return ;
	if (g_meta.clipbo)
		ft_strdel(&(g_meta.clipbo));
	g_meta.clipbo = ft_strdup(cmdl->cmdl + cmdl->pos);
	tmp = cmdl->pos;
	handle_end(cmdl);
	while (tmp < cmdl->pos)
		handle_del(K_BCKSP, cmdl);
}

static void	handle_alt_j(t_cmdl *cmdl)
{
	if (g_meta.clipbo)
		ft_strdel(&(g_meta.clipbo));
	g_meta.clipbo = ft_strndup(cmdl->cmdl, (size_t)(cmdl->pos));
	while (cmdl->pos)
		handle_del(K_BCKSP, cmdl);
}

static void	handle_alt_y(t_cmdl *cmdl)
{
	int	i;

	if (!(g_meta.clipbo))
		return ;
	i = (int)ft_strlen(cmdl->cmdl + cmdl->pos);
	if (!cmdl->cmdl[cmdl->pos])
		ft_stradd(&(cmdl->cmdl), g_meta.clipbo);
	else
		ft_strinsstr(&(cmdl->cmdl), g_meta.clipbo, (size_t)cmdl->pos);
	if (cmdl->pos)
		sh_go_up(cmdl, cmdl->pos);
	sh_putstr(cmdl);
	cmdl->pos += (int)ft_strlen(g_meta.clipbo);
	while (i--)
		sh_go_up(cmdl, cmdl->pos);
}

int			handle_alt_key(int k, t_cmdl *cmdl)
{
	if (k == (int)'k')
		handle_alt_k(cmdl);
	else if (k == (int)'j')
		handle_alt_j(cmdl);
	else if (k == (int)'y')
		handle_alt_y(cmdl);
	return (1);
}
