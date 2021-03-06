/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 20:42:50 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/07 17:52:34 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

# define BI_NBR 5

/*
** bi_cd_to_canonical.c
*/

int		bi_cd_to_canonical(char **str);

/*
** bi_cd.c
*/

int		bi_cd(char **args, char **env);

/*
** exec_builtin.c
*/

int		exec_builtin(t_com *com, int bi, char **env, int *save);
int		exec_builtin_pipe(t_com *com, int bi, char **env);

int		bi_echo(char **args, char **env);
int		bi_setenv(char **args, char **env);
int		bi_unsetenv(char **args, char **env);
int		bi_env(char **args, char **env);

int		bi_exit(t_com *com, char **env);

/*
** is_builtin.c
*/

int		is_builtin(char *str);

#endif
