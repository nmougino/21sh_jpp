/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:47:53 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/07 20:45:58 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"

# include "get_cmdl.h"
# include "env_dep.h"
# include "exec.h"
# include "cmdl_treatment.h"
# include "history.h"
# include "parser.h"
# include "tc_misc.h"
# include "builtins.h"

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

typedef int			(*t_bi)(char **, char **);

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
	t_list			*shenv_save;
	void			(*gcmdl_f)(t_cmdl *cmdl);
	t_bi			bi_tab[BI_NBR];
	t_btree			*ast;
	t_cmdl			cmdl;
}					t_meta;

extern t_meta		g_meta;

void				sh_cmdl_init(t_cmdl *cmdl);

void				metainit(char **env);

int					exec_mother(t_cmdl *cmdl);
void				del_ast(void *d);

// a suppeimer
void	sh_putast(t_btree *r, int l);

#endif
