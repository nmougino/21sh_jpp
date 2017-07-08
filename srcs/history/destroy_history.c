/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 22:11:38 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/08 22:57:30 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta;

void		del_histo(void *p, size_t s)
{
	(void)s;
	(void)p;
	LOGS("NOW ERASING : |%s|\n", (char *)p);
	free((char *)p);
}

void		destroy_history(void)
{
	LOG("HISTO DISPLAY\n");
	histo_display(FD);
	LOG("END\n");
	ft_dlstdel(&HISTO.lst, del_histo, TO_END);
}
