/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:47:53 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/31 16:36:30 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
// # include "sh_lexer.h"
# include "sh_lexer_2.h"

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

# define K_ALT_K	-102
# define K_ALT_J	-122
# define K_ALT_W	-120
# define K_ALT_Y	-91

# define FD			g_meta.fd
# define HISTO		g_meta.history
# define LOG(X)		ft_dprintf(g_meta.fd, X);
# define LOGS(X, Y)	ft_dprintf(g_meta.fd, X, Y);

typedef struct termios	t_termios;

typedef struct		s_cmdl
{
	char			*cmdl;
	int				pos;
}					t_cmdl;

typedef struct		s_history
{
	t_dlist			*lst;
	int				is_in;
	size_t			max;
	t_dlist			*cur;
	char			*save;
}					t_history;

typedef struct		s_shenv
{
	char			*name;
	char			*cont;
}					t_shenv;

typedef struct		s_meta
{
	struct winsize	ws;
	char			*prompt;
	char			*prompt_save;
	t_history		history;
	char			*clipbo;
	int				fd;
	int				edmod;
	t_list			*shenv;
	void			(*gcmdl_f)(t_cmdl *cmdl);
}					t_meta;

extern t_meta		g_meta;

void				sh_cmdl_init(t_cmdl *cmdl);
int					get_cmdl(t_cmdl *cmdl);
void				handle_quotes(t_cmdl *cmdl);
void				handle_back_slash(t_cmdl *cmdl);
void				get_cmdl_loop(t_cmdl *cmdl);
void				get_cmdl_notc(t_cmdl *cmdl);

void				erase_cmdl(t_cmdl *cmdl);

int					handle_action(t_cmdl *cmdl, char *buf);

int					handle_arrows(t_cmdl *cmdl, char *buf);
int					handle_del(char *buf, t_cmdl *cmdl);
int					handle_home(t_cmdl *cmdl);
int					handle_end(t_cmdl *cmdl);
int					handle_alt_arrows(t_cmdl *cmdl, char *buf);
int					handle_alt_key(int k, t_cmdl *cmdl);

void				history_add(char *new);
int					history_move(t_cmdl *cmdl, char *buf);
void				history_exit(t_cmdl *cmdl);
void				histo_display(int fd);

void				erase_cmdl(t_cmdl *cmdl);
void				histo_display(int fd);
void				histo_impose(t_cmdl *cmdl);
void				histo_save(t_cmdl *cmdl);

void				sh_go_do(t_cmdl *cmdl, int pos);
void				sh_go_up(t_cmdl *cmdl, int pos);

void				print_cmdl(t_cmdl *cmdl);
void				sh_restaure_cursor(int i, t_cmdl *cmdl);
void				sh_putstr(t_cmdl *cmdl);

int					sh_putc(int c);

int					terminit(t_termios *tcap, t_termios *save);

int					tc_err_print(int ierr, int e);

void				del_histo(void *p, size_t s);
void				destroy_history(void);

void				metainit(char **env);

t_list				*cmdl_treatment(t_cmdl *cmdl);
void				sh_inhib_exp(t_list *lst);

void				env_init(t_list **shenv, char **env);
void				env_del(void *shenv, size_t s);
void				env_display(t_list *e);

int					term_check(void);

char				*get_env(char *tar);

#endif
