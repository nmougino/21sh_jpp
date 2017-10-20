/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 17:25:13 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/20 17:15:28 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_get_cmdret(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGSEGV)
			ft_putendl_fd("Segmentation Fault", 2);
		else if (WTERMSIG(status) == SIGABRT)
			ft_putendl_fd("Abort", 2);
		else if (WTERMSIG(status) == SIGBUS)
			ft_putendl_fd("Bus Error", 2);
	}
	return (CMD_FAIL);
}

static int	wait_error(void)
{
	char	*str;

	str = NULL;
	str = (errno != EINVAL ? str : "The options argument is not valid.");
	str = (errno != EINTR ? str : "The call is interrupted by a caught signal or the signal does not have the SA_RESTART flag set.");
	str = (errno != ECHILD ? str : "The process specified by pid does not exist or is not a child of the calling process, or the process group specified by pid does not exist or does not have any member process that is a child of the calling process.");
	ft_dprintf(2, "sh: waitpid error: %s\n", str);
	return (CMD_FAIL);
}

static int	do_fork(t_com *com, char **env, int *save)
{
	pid_t	pid;
	int		i;

	i = CMD_SUCCESS;
	if ((pid = ft_fork("sh")) == -1)
		return (CMD_FAIL);
	else if (pid > 0)
	{
		write_hd(com, save);
		if (waitpid(pid, &i, 0) == -1)
			return(wait_error());
	}
	else if (!pid)
	{
		if (com->heredoc)
			clodup(com->hdfd, 0);
		exec_simple(com->i, com, env);
	}
	return (ft_get_cmdret(i));
}

static int	launch_simple(t_btree *r)
{
	int		j;
	t_com	com;
	char	**env;
	int		save[3];

	env = env_conv();
	create_simple(&com, (t_list *)(r->data));
	handle_redir(&com, save);
	if (com.heredoc)
		pipe(com.hdfd);
	if (is_builtin(com.com_name))
		return (exec_builtin(&com, is_builtin(com.com_name) - 1, env, save));
	j = do_fork(&com, env, save);
	com_del(&com);
	ft_arrdel((void***)&env);
	if (!com.heredoc)
		restore_redir(save);
	return (!j ? CMD_SUCCESS : CMD_FAIL);
}

int			exec_ast(t_btree *r)
{
	if (r)
	{
		if (((t_token *)(((t_list *)(r->data))->content))->type == OP_CONTROL)
			return (apply_op(r));
		else
			return (launch_simple(r));
	}
	return (CMD_FAIL);
}
