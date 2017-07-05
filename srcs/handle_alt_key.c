/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_alt_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 00:12:11 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/05 08:22:10 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta;

static void	sh_erase_shit(t_cmdl *cmdl)
{
	int	tmp;

	tmp = cmdl->pos;
	handle_end(cmdl);
	while (tmp != cmdl->pos)
		handle_del(K_BCKSP, cmdl);
	sh_go_up(cmdl, cmdl->pos);
}

static void	handle_alt_k(t_cmdl *cmdl)
{
	if (g_meta.save)
		free(g_meta.save);
	g_meta.save = ft_strdup(cmdl->cmdl + cmdl->pos);
	sh_go_up(cmdl, cmdl->pos);
	sh_erase_shit(cmdl);
	print_cmdl(cmdl);
}

static void	handle_alt_u(t_cmdl *cmdl)
{
	(void)cmdl;
}

static void	handle_alt_w(t_cmdl *cmdl)
{
	(void)cmdl;
}

static void	handle_alt_y(t_cmdl *cmdl)
{
	(void)cmdl;
}

int			handle_alt_key(int k, t_cmdl *cmdl)
{
	if (k == K_ALT_K)
		handle_alt_k(cmdl);
	else if (k == K_ALT_U)
		handle_alt_u(cmdl);
	else if (k == K_ALT_W)
		handle_alt_w(cmdl);
	else if (k == K_ALT_Y)
		handle_alt_y(cmdl);
	return (1);
}
