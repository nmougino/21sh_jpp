/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metainit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:11:56 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/16 20:21:43 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	metainit(void)
{
	extern t_meta	g_meta;
	ioctl(0, TIOCGWINSZ, &(g_meta.ws));
	g_meta.prompt = "hafh aiweh fiah efihaweipfh apwhefiuhawefh aiowehfiwaoehf aw>> ";
}
