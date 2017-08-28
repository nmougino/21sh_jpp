/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 06:12:24 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/28 06:16:06 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_add(char *name, char *cont)
{
	t_shenv	new;

	new.name = ft_strdup(name);
	new.cont = ft_strdup(cont);
	ft_lstadd_end(&(g_meta.shenv), ft_lstnew(&new, sizeof(t_shenv)));
}
