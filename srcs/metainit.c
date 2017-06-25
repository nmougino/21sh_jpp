/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metainit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:11:56 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/25 18:38:43 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	metainit(void)
{
	extern t_meta	g_meta;
	ioctl(0, TIOCGWINSZ, &(g_meta.ws));
	g_meta.prompt = "prompt >> ";
	g_meta.prompt_save = "prompt >> ";
	g_meta.fd = open("./log.txt", O_WRONLY | O_TRUNC | O_CREAT);
}
