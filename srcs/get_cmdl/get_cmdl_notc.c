/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl_notc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:45:08 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/11 18:57:28 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_cmdl_notc(t_cmdl *cmdl)
{
	ft_putstr(g_meta.prompt);
	get_next_line(0, &(cmdl->cmdl));
	ft_printf("fin d'edition\n");
}
