/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:23:01 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/10 21:28:19 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_init(t_list **shenv, char **env)
{
	t_shenv	new;
	size_t	i;

	*shenv = NULL;
	if (!env || !*env)
		return ;
	while (*env)
	{
		i = (size_t)ft_strcloc('=', *env);
		new.name = ft_strnew(i);
		ft_strncpy(new.name, *env, i);
		new.cont = ft_strdup((*env) + i + 1);
		ft_lstadd_end(shenv, ft_lstnew(&new, sizeof(t_shenv)));
		++env;
	}
}
