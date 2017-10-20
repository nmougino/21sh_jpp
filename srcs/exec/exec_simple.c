/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 17:16:09 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/20 17:14:06 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*execve_error(void)
{
	char	*str;

	str = NULL;
	str = (errno == E2BIG) ? EXEC_E2BIG : str;
	str = (errno == EACCES) ? EXEC_EACCES : str;
	str = (errno == EFAULT) ? EXEC_EFAULT : str;
	str = (errno == EIO) ? EXEC_EIO : str;
	str = (errno == ELOOP) ? EXEC_ELOOP : str;
	str = (errno == ENAMETOOLONG) ? EXEC_ENAMETOOLONG : str;
	str = (errno == ENOENT) ? EXEC_ENOENT : str;
	str = (errno == ENOEXEC) ? EXEC_ENOEXEC : str;
	str = (errno == ENOMEM) ? EXEC_ENOMEM : str;
	str = (errno == ENOTDIR) ? EXEC_ENOTDIR : str;
	str = (errno == ETXTBSY) ? EXEC_ETXTBSY : str;
	return (str ? str : "Unknow error, please check errno");
}

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

void		exec_simple(int i, t_com *com, char **env)
{
	if (i != 1)
	{
		if (i)
			i = cmd_err(i, com->com_name);
		bi_exit(com, env);
		exit(CMD_FAIL);
	}
	else
		execve(com->cmd_path, com->cmd_args, env);
	ft_dprintf(2, "sh: permission denied: %s\n(%s)\n", com->com_name,
		execve_error());
	bi_exit(com, env);
	exit(-1);
}
