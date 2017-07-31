/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 10:42:55 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/31 22:22:24 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		history_add_forceps(void)
{
	t_dlist	*cur;

	cur = HISTO.lst;
	while (cur->next)
		cur = cur->next;
	if (cur->prev)
		cur->prev->next = NULL;
	ft_dlstdel(&cur, del_histo, TO_END);
}

void			history_add(char *new)
{
	if (!(new && *new))
		return ;
	if (ft_dlstlen(HISTO.lst) == HISTO.max)
		history_add_forceps();
	if (!(HISTO.lst) || !ft_strequ(new, (char *)((HISTO.lst)->content)))
		ft_dlstadd(&(HISTO.lst), ft_dlstnew(new, ft_strlen(new) + 1));
}
