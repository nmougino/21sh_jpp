/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:09:26 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/14 15:42:00 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_CMDL_H
# define GET_CMDL_H

# include "shell.h"

# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

typedef struct termios	t_termios;

typedef struct		s_cmdl
{
	char			*cmdl;
	int				pos;
}					t_cmdl;

/*
** get_cmdl.c
*/

int					get_cmdl(t_cmdl *cmdl);
void				get_cmdl_loop(t_cmdl *cmdl);

/*
** get_cmdl_notc.c
*/

void				get_cmdl_notc(t_cmdl *cmdl);

/*
** handle_actions.c
*/

int					handle_action(t_cmdl *cmdl, char *buf);

/*
** handle_alt_arrows.c
*/

int					handle_alt_arrows(t_cmdl *cmdl, char *buf);

/*
** handle_alt_key.c
*/

int					handle_alt_key(int k, t_cmdl *cmdl);

/*
** handle_arrows.c
*/

int					handle_arrows(t_cmdl *cmdl, char *buf);

/*
** handle_back_slash.c
*/

void				handle_back_slash(t_cmdl *cmdl);

/*
** handle_del.c
*/

int					handle_del(char *buf, t_cmdl *cmdl);

/*
** handle_home_end.c
*/

int					handle_home(t_cmdl *cmdl);
int					handle_end(t_cmdl *cmdl);

/*
** handle_quotes.c
*/

void				handle_quotes(t_cmdl *cmdl);

/*
** print_cmdl.c
*/

void				sh_putstr(t_cmdl *cmdl);
void				sh_restaure_cursor(int i, t_cmdl *cmdl);
void				print_cmdl(t_cmdl *cmdl);


#endif
