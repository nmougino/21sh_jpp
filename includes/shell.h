/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:47:53 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/17 19:00:07 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

# define ERR_NO_NAME 0
# define ERR_TGETENT_FAIL 1
# define ERR_TCGETATTR_FAIL 2
# define ERR_TCSETATTR_FAIL 3

# define K_UP_A		"\033[A"
# define K_DO_A		"\033[B"
# define K_RI_A		"\033[C"
# define K_LE_A		"\033[D"
# define K_BCKSP	"\177"
# define K_DEL		"\033[3~"
# define K_HOME		"\033[H"
# define K_END		"\033[F"


typedef struct		termios
					t_termios;

typedef struct		s_meta
{
	struct winsize	ws;
	char			*prompt;
	int				fd; // pour les logs, penser a le supprimer
}					t_meta;

extern t_meta		g_meta;

char				*get_cmdl(void);
int					handle_arrows(char *buf, size_t *pos, char *cmdl);
int					handle_del(char *buf, size_t *pos, char *cmdl);

int					tc_go_up(size_t pos);
int					tc_go_do(size_t pos);

int					sh_putc(int c);

void				print_cmdl(char *cmdl, size_t pos);

void				terminit(t_termios *tcap, t_termios *save);

int					tc_err_print(int ierr, int e);

void				metainit(void);

#endif
