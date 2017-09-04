/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:38:17 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/04 19:23:11 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** change la valeur d'un maillon de l'environement, uniquement s'il existe
*/

void	env_set(char *tar, char *new_cont)
{
	int		i;
	t_list	*tmp;

	i = g_meta.shenv == g_meta.shenv_save ? 1 : 0;
	tmp = i ? g_meta.shenv : g_meta.shenv_save;
	while (tmp && ft_strcmp(((t_shenv*)(tmp->content))->name, tar))
		tmp = tmp->next;
	if (!tmp)
		env_add(tar, new_cont);
	else
	{
		ft_strdel(&(((t_shenv*)(tmp->content))->cont));
		((t_shenv*)(tmp->content))->cont = ft_strdup(new_cont);
	}
	if (i)
		g_meta.shenv_save = g_meta.shenv;
}
