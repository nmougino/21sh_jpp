/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 20:52:54 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/16 21:54:32 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	bi_exit(t_com *com, char **env)
{
	int	i;

	i = !(com->cmd_args) || !(com->cmd_args)[1] ? 0
		: ft_atoi((com->cmd_args)[1]);
	com_del(com);
	ft_arrdel((void***)&env);
	ft_strdel(&(g_meta.cmdl.cmdl));
	ft_btreedel(&g_meta.ast, del_ast);
	if (g_meta.shenv)
		ft_lstdel(&(g_meta.shenv), env_del);
	else
		ft_lstdel(&(g_meta.shenv_save), env_del);
	destroy_history();
	close(g_meta.fd);
	if (g_meta.clipbo)
		free(g_meta.clipbo);
	return (i);
}
