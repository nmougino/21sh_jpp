/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 22:24:05 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/20 17:11:49 by nmougino         ###   ########.fr       */
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
		g_meta.prompt = g_meta.prompt_save;
		ft_putstr(g_meta.prompt);
		g_meta.cmdl.cmdl = ft_strdup("");
	}
}

static void	handle_wch(int s)
{
	(void)s;
	ioctl(0, TIOCGWINSZ, &(g_meta.ws));
}

void		mapsigs(void)
{
	int	i;

	i = 1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGINT, handle_c);
	signal(SIGWINCH, handle_wch);
}
