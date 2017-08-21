/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 17:16:09 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/21 18:38:55 by nmougino         ###   ########.fr       */
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

int			exec_simple(t_list *lst)
{
	pid_t	pid;
	t_com	com;
	int		i;
	char	**env;

	i = create_simple(&com, lst);
	env = env_conv();
	if (!(pid = fork()))
	{
		ft_putstrarr(com.cmd_args);
		handle_redir(&com);
		if (!i)
			exit(0);
		else if (i != 1)
			exit(cmd_err(i, com.com_name));
		else
			i = execve(com.cmd_path, com.cmd_args, env);
		ft_dprintf(2, "sh: permission denied: %s\n(%s)\n", com.com_name,
			execve_error());
		exit(-1);
	}
	waitpid(pid, &i, 0);
	return (i);
}
