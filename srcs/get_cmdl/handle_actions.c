/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 11:35:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/08 20:56:57 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	detect_alt_keys(char *buf)
{
	if (buf[0] == -53 && buf[1] == -102)
		return ((int)'k');
	else if (buf[0] == -30 && buf[1] == -120 && buf[2] == -122)
		return ((int)'j');
	else if (buf[0] == -62 && buf[1] == -91)
		return ((int)'y');
	return (0);
}

int			handle_action(t_cmdl *cmdl, char *buf)
{
	if (ft_strequ(buf, K_UP_A) || ft_strequ(buf, K_DO_A))
		return (history_move(cmdl, buf));
	else if (ft_strequ(buf, K_RI_A) || ft_strequ(buf, K_LE_A))
		return (handle_arrows(cmdl, buf));
	else if (HISTO.is_in)
		history_exit(cmdl);
	if (detect_alt_keys(buf))
		return (handle_alt_key(detect_alt_keys(buf), cmdl));
	else if (ft_strequ(buf, K_BCKSP) || ft_strequ(buf, K_DEL))
		return (handle_del(buf, cmdl));
	else if (ft_strequ(buf, K_HOME))
		return (handle_home(cmdl));
	else if (ft_strequ(buf, K_END))
		return (handle_end(cmdl));
	else if (ft_strequ(buf, K_ALT_LE_A) || ft_strequ(buf, K_ALT_RI_A) ||
		ft_strequ(buf, K_ALT_UP_A) || ft_strequ(buf, K_ALT_DO_A))
		return (handle_alt_arrows(cmdl, buf));
	else if (!ft_isprint(buf[0]) || buf[0] == '\t')
		return (1);
	return (0);
}
