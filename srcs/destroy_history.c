/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 22:11:38 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/26 22:18:59 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern t_meta	g_meta;

static void	del_histo(void *p, size_t s)
{
	(void)s;
	free((char *)p);
}

void		destroy_history(void)
{
	ft_printf("destruction histo\n");
	ft_dlstdel(&g_meta.history.lst, del_histo, TO_END);
	ft_printf("destruction terminee\n");
}
