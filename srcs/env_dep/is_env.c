/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:24:32 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/29 12:31:42 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Identifie si la cible est dans l'env, en scannant la liste globale
*/

int	is_env(char *tar)
{
	t_list	*e;

	e = g_meta.shenv;
	while (e)
	{
		if (ft_strequ(((t_shenv*)(e->content))->name, tar))
			return (1);
		e = e->next;
	}
	return (0);
}

/*
** Meme que la precendente mais dans un env char **
*/

int	is_env_local(char **env, char *tar)
{
	while (env)
	{
		if (ft_strnequ(tar, *env, ft_strlen(tar)))
			return (1);
		++env;
	}
	return (0);
}
