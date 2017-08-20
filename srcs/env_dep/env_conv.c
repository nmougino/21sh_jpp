/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:40:57 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/20 18:05:04 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**env_conv(void)
{
	char	**ans;
	t_list	*shenv;
	size_t	len;
	size_t	i;

	shenv = g_meta.shenv;
	len = ft_lstlen(shenv);
	i = 0;
	ans = malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		ans[i] = ft_strnew(ft_strlen(((t_shenv*)(shenv->content))->name)
		+ ft_strlen(((t_shenv*)(shenv->content))->cont) + 1);
		ft_strcpy(ans[i], ((t_shenv*)(shenv->content))->name);
		ft_strcat(ans[i], "=");
		ft_strcat(ans[i], ((t_shenv*)(shenv->content))->cont);
		shenv = shenv->next;
		++i;
	}
	return (ans);
}
