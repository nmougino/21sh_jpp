/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_misc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:25:28 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/12 14:47:30 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TC_MISC_H
# define TC_MISC_H

# include "shell.h"

/*
** err_dep.c
*/

int		tc_err_print(int ierr, int e);

/*
** sh_go_doup.c
*/

void	sh_go_do(t_cmdl *cmdl, int pos);
void	sh_go_up(t_cmdl *cmdl, int pos);

/*
** tc_putc.c
*/

int		sh_putc(int c);

/*
** terminit.c
*/

int		terminit(t_termios *tcap, t_termios *save);

#endif
