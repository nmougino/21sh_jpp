/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 23:47:21 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/28 06:05:09 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_env(char *tar)
{
	t_list	*tmp;

	tmp = g_meta.shenv;
	while (tmp)
	{
		if (ft_strequ(((t_shenv *)(tmp->content))->name, tar))
			return (((t_shenv *)(tmp->content))->cont);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env_local(char **env, char *tar)
{
	while (*env)
	{
		if (ft_strnequ(*env, tar, ft_strlen(tar)))
			return (*env + ft_strlen(tar) + 1);
		++env;
	}
	return (NULL);
}
