/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 22:24:05 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/03 17:49:41 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_c(int s)
{
	(void)s;
	ft_putendl("");
	if (!g_meta.exec)
	{
		sh_cmdl_init(&(g_meta.cmdl));
		ft_putstr(g_meta.prompt);
		g_meta.cmdl.cmdl = ft_strdup("");
	}
}

void		mapsigs(void)
{
	signal(SIGINT, handle_c);
}
