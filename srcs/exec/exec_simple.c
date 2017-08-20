/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 17:16:09 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/20 19:47:29 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	cmd_err(int i, char *com_name)
{
	if (i == -1)
		ft_dprintf(2, "sh: command not found: %s\n", com_name);
	else if (i == -2)
		ft_dprintf(2, "sh: no such file or directory: %s\n", com_name);
	else
		ft_dprintf(2, "sh: bad error\n");
	return (-1);
}

int		exec_simple(t_list *lst)
{
	pid_t	pid;
	t_com	com;
	int		i;
	char	**env;

	i = create_simple(&com, lst);
	env = env_conv();
	if (!(pid = fork()))
	{
		handle_redir(&com);
		if (!i)
			exit(0);
		else if (i != 1)
			exit (cmd_err(i, com.com_name));
		else
			execve(com.cmd_path, com.cmd_args, env);
		ft_dprintf(2, "sh: permission denied: %s\n", com.com_name);
		exit(-1);
	}
	waitpid(pid, &i, 0);
	ft_printf("retour de la commande %s : %d\n", com.com_name, i);
	return (i);
}

/*

1 - parser les redirection
2 - parser les arguments, et les commandes.

forker.
	executer les redirections.
	gerer les erreurs
	executer la commande

*/
