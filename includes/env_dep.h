/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dep.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:36:45 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/14 15:41:50 by nmougino         ###   ########.fr       */
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
** env_del.c
*/

void			env_del(void *shenv, size_t s);

/*
** env_display.c
*/

void			env_display(t_list *e);

/*
** env_init.c
*/

void			env_init(t_list **shenv, char **env);

/*
** get_env.c
*/

char			*get_env(char *tar);

#endif
