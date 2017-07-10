/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:39:02 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/11 00:25:13 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_del(void *shenv, size_t s)
{
	(void)s;
	free(((t_shenv *)shenv)->name);
	free(((t_shenv *)shenv)->cont);
	free(shenv);
}
