/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 06:12:24 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/03 23:49:46 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_add(char *name, char *cont)
{
	t_shenv	new;

	new.name = ft_strdup(name);
	new.cont = ft_strdup(cont);
	if (g_meta.shenv == g_meta.shenv_save)
	{
		ft_lstadd_end(&(g_meta.shenv), ft_lstnew(&new, sizeof(t_shenv)));
		g_meta.shenv_save = g_meta.shenv;
	}
	else
		ft_lstadd_end(&(g_meta.shenv_save), ft_lstnew(&new, sizeof(t_shenv)));
}
