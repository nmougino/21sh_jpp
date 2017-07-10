/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:47:47 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/10 20:49:46 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_display(t_list *e)
{
	t_shenv	*c;

	c = (t_shenv *)e->content;
	ft_printf("%s=%s\n", c->name, c->cont);
}
