/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 23:47:21 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/12 05:37:45 by nmougino         ###   ########.fr       */
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
