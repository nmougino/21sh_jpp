/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:35:35 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/28 21:36:34 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	write_hd(t_com *com, int save[])
{
	if (com->heredoc)
	{
		clodup(com->hdfd, 1);
		ft_putstr(com->heredoc);
		restore_redir(save);
		close(com->hdfd[1]);
	}
}
