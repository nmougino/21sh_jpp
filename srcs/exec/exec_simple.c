/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 17:16:09 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/19 19:26:22 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** This function WILL NOT fork in order to create a new process.
*/

void		exec_simple(t_com *com)
{
	handle_redir(com);
	exit (0);
}

void		normal_command(t_list *lst)
{
	pid_t	pid;
	t_com	com;
	int		i;
	char	**env;

	i = create_simple(&com, lst)
	env = env_convert();
	if (!(pid = fork()))
	{
		handle_redir(com);
		if (!i)
			exit(0);
		else if (i != 1)
			exit (cmd_err(i));
		else
			execve(com.cmd_path, com.cmd_args, env);
	}
	waitpid(pid, NULL, NULL);
}

/*

1 - parser les redirection
2 - parser les arguments, et les commandes.

forker.
	executer les redirections.
	gerer les erreurs
	executer la commande

*/
