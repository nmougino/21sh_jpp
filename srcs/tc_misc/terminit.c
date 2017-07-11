/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:44:14 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/11 18:40:21 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	terminit(t_termios *tcap, t_termios *save)
{
	char	*name;
	int		e;

	if (!(name = getenv("TERM")))
		return(tc_err_print(ERR_NO_NAME, 0));
	if ((e = tgetent(NULL, name)) != 1)
		return(tc_err_print(ERR_TGETENT_FAIL, e));
	if (tcgetattr(0, tcap) == -1)
		return(tc_err_print(ERR_TCGETATTR_FAIL, 0));
	if (tcgetattr(0, save) == -1)
		return(tc_err_print(ERR_TCGETATTR_FAIL, 0));
	tcap->c_lflag &= ~((unsigned long)(ECHO | ECHOE | ECHOK | ECHONL | ICANON));
	tcap->c_cc[VMIN] = 1;
	tcap->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, tcap) == -1)
		return(tc_err_print(ERR_TCSETATTR_FAIL, 0));
	return (term_check());
}
