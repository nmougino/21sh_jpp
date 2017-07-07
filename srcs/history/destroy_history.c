/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 22:11:38 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/06 15:24:16 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta;

void		del_histo(void *p, size_t s)
{
	(void)s;
	free((char *)p);
}

void		destroy_history(void)
{
	ft_dlstdel(&HISTO.lst, del_histo, TO_END);
}
