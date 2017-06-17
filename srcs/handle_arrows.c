/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:31:32 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/17 17:33:08 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		handle_arrows(char *buf, size_t *pos, char *cmdl)
{
	if (ft_strequ(buf, K_UP_A))
		return (1);
	else if (ft_strequ(buf, K_DO_A))
		return (1);
	if (ft_strequ(buf, K_RI_A) && *pos < ft_strlen(cmdl))
	{
		if (!tc_go_do(*pos))
			ft_putstr("\033[1C");
		*pos += (*pos < ft_strlen(cmdl)) ? 1 : 0;
	}
	else if (ft_strequ(buf, K_LE_A) && *pos)
	{
		if (!tc_go_up(*pos))
			ft_putstr("\033[1D");
		*pos -= *pos ? 1 : 0;
	}
	return (1);
}
