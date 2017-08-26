/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 20:44:16 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/26 21:02:17 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	bi_echo(t_com *com, char **env)
{
	(void)com;
	(void)env;
	ft_printf("sh: builtin active ::: 'echo'\n");
	return (0);
}

int	bi_cd(t_com *com, char **env)
{
	(void)com;
	(void)env;
	ft_printf("sh: builtin active ::: 'cd'\n");
	return (0);
}

int	bi_setenv(t_com *com, char **env)
{
	(void)com;
	(void)env;
	ft_printf("sh: builtin active ::: 'setenv'\n");
	return (0);
}

int	bi_unsetenv(t_com *com, char **env)
{
	(void)com;
	(void)env;
	ft_printf("sh: builtin active ::: 'unsetenv'\n");
	return (0);
}

int	bi_env(t_com *com, char **env)
{
	(void)com;
	(void)env;
	ft_printf("sh: builtin active ::: 'env'\n");
	return (0);
}

int	bi_exit(t_com *com, char **env)
{
	(void)com;
	(void)env;
	ft_printf("sh: builtin active ::: 'exit'\n");
	return (0);
}

int	exec_builtin(t_com *com, int bi, char **env)
{
	int	i;

	i = g_meta.bi_tab[bi](com->cmd_args, env);
	com_del(com);
	ft_arrdel((void**)env);
	return (i);
}
