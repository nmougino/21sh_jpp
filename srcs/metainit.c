/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metainit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:11:56 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/26 21:02:50 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	bi_init(void)
{
	g_meta.bi_tab[0] = bi_echo;
	g_meta.bi_tab[1] = bi_cd;
	g_meta.bi_tab[2] = bi_setenv;
	g_meta.bi_tab[3] = bi_unsetenv;
	g_meta.bi_tab[4] = bi_env;
	g_meta.bi_tab[5] = bi_exit;
}

void		metainit(char **env)
{
	ioctl(0, TIOCGWINSZ, &(g_meta.ws));
	g_meta.prompt = "prompt >> ";
	g_meta.prompt_save = "prompt >> ";
	g_meta.fd = open("./log.txt", O_WRONLY | O_TRUNC | O_CREAT);
	HISTO.lst = NULL;
	HISTO.cur = NULL;
	HISTO.is_in = 0;
	HISTO.max = 10;
	HISTO.save = NULL;
	g_meta.clipbo = NULL;
	env_init(&(g_meta.shenv), env);
	bi_init();
}
