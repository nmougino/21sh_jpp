/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_dep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:52:50 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/11 18:39:21 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	tc_err_print(int ierr, int e)
{
	if (ierr == ERR_NO_NAME)
		ft_putendl_fd(
			"ERR_NO_NAME: Specify a terminal type with 'setenv TERM'.", 2);
	else if (ierr == ERR_TGETENT_FAIL)
		if (e < 0)
			ft_putendl_fd(
			"ERR_TGETENT_FAIL: Could not access the termcap data base.", 2);
		else
			ft_putendl_fd(
				"ERR_TGETENT_FAIL: Terminal type is not defined.", 2);
	else if (ierr == ERR_TCGETATTR_FAIL)
		ft_putendl_fd("ERR_TCGETATTR_FAIL", 2);
	else if (ierr == ERR_TCSETATTR_FAIL)
		ft_putendl_fd("ERR_TCSETATTR_FAIL", 2);
	return (0);
}
