/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 20:44:16 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/16 21:51:56 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** bi:5 est le code pour exit, builtin special qui va s'occuper de dtruire la
** memoire reservee en amont de son appel.
*/

int	exec_builtin(t_com *com, int bi, char **env, int *save)
{
	int	i;

	if (bi == 5)
		exit(bi_exit(com, env));
	i = g_meta.bi_tab[bi](com->cmd_args, env);
	com_del(com);
	ft_arrdel((void***)&env);
	restore_redir(save);
	return (i);
}

int	exec_builtin_pipe(t_com *com, int bi, char **env)
{
	int	i;

	if (bi == 5)
		exit(bi_exit(com, env));
	i = g_meta.bi_tab[bi](com->cmd_args, env);
	bi_exit(com, env);
	return (i);
}
