/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:30:55 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/01 10:22:08 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_del(char *buf, t_cmdl *cmdl)
{
	if (ft_strequ(buf, K_BCKSP) && cmdl->pos)
	{
		ft_strremchar(cmdl->cmdl, (size_t)(cmdl->pos - 1));
		sh_go_up(cmdl, cmdl->pos);
		--(cmdl->pos);
		if (cmdl->pos)
			sh_go_up(cmdl, cmdl->pos);
		print_cmdl(cmdl);
	}
	else if (ft_strequ(buf, K_DEL) && (cmdl->cmdl[cmdl->pos]))
	{
		ft_strremchar(cmdl->cmdl, (size_t)(cmdl->pos));
		sh_go_up(cmdl, cmdl->pos);
		print_cmdl(cmdl);
	}
	return (1);
}
