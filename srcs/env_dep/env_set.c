/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:38:17 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/03 21:49:56 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** change la valeur d'un maillon de l'environement, uniquement s'il existe
*/

void	env_set(char *tar, char *new_cont)
{
	t_list	*tmp;

	tmp = g_meta.shenv;
	while (tmp && ft_strcmp(((t_shenv*)(tmp->content))->name, tar))
		tmp = tmp->next;
	if (!tmp)
		env_add(tar, new_cont);
	ft_strdel(&(((t_shenv*)(tmp->content))->cont));
	((t_shenv*)(tmp->content))->cont = ft_strdup(new_cont);
	g_meta.shenv_save = g_meta.shenv;
}
