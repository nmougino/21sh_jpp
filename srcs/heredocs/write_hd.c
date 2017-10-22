/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:35:35 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/22 20:26:02 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	write_hd(t_com *com, int save[])
{
	if (com->heredoc)
	{
		clodup(com->hdfd, 1);
		ft_putstr(com->heredoc);
		if (save)
			restore_redir(save);
		close(com->hdfd[1]);
	}
}
