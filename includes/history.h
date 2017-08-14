/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:19:10 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/14 15:26:18 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

typedef struct		s_history
{
	t_dlist			*lst;
	int				is_in;
	size_t			max;
	t_dlist			*cur;
	char			*save;
}					t_history;

/*
** destroy_history.c
*/

void				del_histo(void *p, size_t s);
void				destroy_history(void);

/*
** history_add.c
*/

void				history_add(char *new);

/*
** history_dep.c
*/

int					history_move(t_cmdl *cmdl, char *buf);
void				history_exit(t_cmdl *cmdl);

/*
** history_misc.c
*/

void				erase_cmdl(t_cmdl *cmdl);
void				histo_display(int fd);
void				histo_impose(t_cmdl *cmdl);
void				histo_save(t_cmdl *cmdl);

#endif
