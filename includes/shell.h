/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:47:53 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/26 22:13:31 by nmougino         ###   ########.fr       */
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
# define K_ALT_UP_A	"\033\033[A"
# define K_ALT_DO_A	"\033\033[B"
# define K_ALT_RI_A	"\033\033[C"
# define K_ALT_LE_A	"\033\033[D"


typedef struct		termios
					t_termios;

typedef struct		s_history
{
	t_dlist			*lst;
	int				is_in;
	int				max;
	t_dlist			*cur;
}					t_history;

typedef struct		s_meta
{
	struct winsize	ws;
	char			*prompt;
	char			*prompt_save;
	t_history		history;
	int				fd; // pour les logs, penser a le supprimer
}					t_meta;

typedef struct		s_cmdl
{
	char			*cmdl;
	int				pos;
}					t_cmdl;

extern t_meta		g_meta;

void				sh_cmdl_init(t_cmdl *cmdl);
int					get_cmdl(t_cmdl *cmdl);

int					handle_arrows(t_cmdl *cmdl, char *buf);
int					handle_del(char *buf, t_cmdl *cmdl);
int					handle_home(t_cmdl *cmdl);
int					handle_end(t_cmdl *cmdl);
int					handle_alt_arrows(t_cmdl *cmdl, char *buf);

void				history_add(char *new);
int					history_move(t_cmdl *cmdl, char *buf);


void				print_cmdl(t_cmdl *cmdl);
void				sh_restaure_cursor(int i, t_cmdl *cmdl);
void				sh_putstr(t_cmdl *cmdl);

int					sh_putc(int c);

void				terminit(t_termios *tcap, t_termios *save);

int					tc_err_print(int ierr, int e);

void				destroy_history(void);

void				metainit(void);

#endif
