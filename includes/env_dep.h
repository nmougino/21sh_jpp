/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dep.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:36:45 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/04 20:11:56 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_DEP_H
# define ENV_DEP_H

# include "shell.h"

typedef struct	s_shenv
{
	char		*name;
	char		*cont;
}				t_shenv;

/*
** env_add.c
*/

void			env_add(char *name, char *cont);

/*
** env_conv.c
*/

char			**env_conv(void);

/*
** env_del.c
*/

void			env_del(void *shenv, size_t s);

/*
** env_display.c
*/

void			env_display(void);
void			env_display_local(char **str);

/*
** env_init.c
*/

void			misc_env(void);
void			env_init(t_list **shenv, char **env);

/*
** env_set.c
*/

void			env_set(char *name, char *cont);

/*
** env_set.c
*/

void			env_unset(char *name);

/*
** get_env.c
*/

char			*get_env(char *tar);
char			*get_env_local(char **env, char *tar);

/*
** is_env.c
*/

int				is_env(char *tar);
int				is_env_local(char **env, char *tar);

#endif
