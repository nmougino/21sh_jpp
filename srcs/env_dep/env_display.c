/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:47:47 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/30 17:39:08 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	env_do_display(t_list *e)
{
	t_shenv	*c;

	c = (t_shenv *)e->content;
	ft_printf("%s=%s\n", c->name, c->cont);
}

void		env_display(void)
{
	ft_lstiter(g_meta.shenv, env_do_display);
}

void		env_display_local(char **str)
{
	ft_putendl(*str);
}
