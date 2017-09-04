/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 19:48:58 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/04 20:15:41 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	delf(void *e, size_t s)
{
	t_shenv *el;

	(void)s;
	el = e;
	free(el->name);
	free(el->cont);
}

void		env_unset(char *tar)
{
	int		i;
	t_list	*tar_el;

	i = g_meta.shenv == g_meta.shenv_save ? 1 : 0;
	tar_el = g_meta.shenv;
	while (tar_el && !ft_strequ(((t_shenv*)(tar_el->content))->name, tar))
		tar_el = tar_el->next;
	if (!tar_el)
		return ;
	ft_lstrem(&(g_meta.shenv), tar_el, delf);
	if (i)
		g_meta.shenv_save = g_meta.shenv;
}
