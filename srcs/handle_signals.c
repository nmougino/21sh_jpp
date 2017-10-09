/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 22:24:05 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/05 00:40:16 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_c(int s)
{
	(void)s;
	if (!g_meta.exec)
	{
		ft_putendl("");
		sh_cmdl_init(&(g_meta.cmdl));
		ft_putstr(g_meta.prompt);
		g_meta.cmdl.cmdl = ft_strdup("");
	}
}

static void	do_nothing(int s)
{
	if (!g_meta.exec)
	{
		ft_printf(" This signal is not supported : %d\n", s);
		sh_cmdl_init(&(g_meta.cmdl));
		ft_putstr(g_meta.prompt);
		g_meta.cmdl.cmdl = ft_strdup("");
	}
	else
		ft_printf("\nThis signal is not supported : %d\n", s);
}

void		mapsigs(void)
{
	signal(SIGINT, handle_c);
	signal(18, do_nothing);
	signal(19, do_nothing);
}
