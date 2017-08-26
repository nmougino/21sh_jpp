/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 20:42:50 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/26 21:02:28 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

# define BI_NBR 6

/*
** exec_builtin.c
*/

int	exec_builtin(t_com *com, int bi, char **env);

int	bi_echo(t_com *com, char **env);
int	bi_cd(t_com *com, char **env);
int	bi_setenv(t_com *com, char **env);
int	bi_unsetenv(t_com *com, char **env);
int	bi_env(t_com *com, char **env);
int	bi_exit(t_com *com, char **env);


/*
** is_builtin.c
*/

int	is_builtin(char *str);

#endif
