/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:46:11 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/05 17:00:10 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		clodup(int *fd, int i)
{
	if (!fd)
		return ;
	if (i)
	{
		close(fd[0]);
		dup2(fd[1], 1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}

static int		exec_pipe_left(t_btree *r, int *fd)
{
	int		i;
	pid_t	pid;
	t_com	com;
	char	**env;

	env = env_conv();
	i = create_simple(&com, (t_list *)(r->data));
	if (!(pid = ft_fork("sh")))
	{
		clodup(fd, 1);
		if ((pid = is_builtin(com.com_name)))
			exit (exec_builtin_pipe(&com, pid - 1, env));
		exec_simple(i, &com, env);
	}
	else
	{
		waitpid(pid, &i, 0);
		close(fd[1]);
		com_del(&com);
		ft_arrdel((void***)&env);
		return (i);
	}
	return (CMD_FAIL);
}

static int		pipe_left(t_btree *r, int *fd)
{
	if (((t_token *)(((t_list *)(r->data))->content))->type == OP_CONTROL)
		return (apply_pipe(r, fd));
	else
		return (exec_pipe_left(r, fd));
}

static pid_t	pipe_right(t_btree *prev, t_btree *r, int *fd, int *pfd)
{
	int		i;
	pid_t	pid;
	t_com	com;
	char	**env;

	env = env_conv();
	i = create_simple(&com, (t_list *)(r->data));
	if (!(pid = ft_fork("sh")))
	{
		clodup(fd, 0);
		clodup(pfd, 1);
		exec_simple(i, &com, env);
	}
	else if (pid)
	{
		pipe_left(prev->left, fd);
		waitpid(pid, &i, 0);
		if (pfd)
			close(pfd[1]);
		com_del(&com);
		ft_arrdel((void***)&env);
		return (i);
	}
	return (CMD_FAIL);
}

int				apply_pipe(t_btree *r, int *pfd)
{
	int	fd[2];
	int i;

	if (pipe(fd) == -1)
		return (ft_dprintf(2, "sh: pipe failed\n") ? -1 : -1);
	i = pipe_right(r, r->right, fd, pfd);
	close(fd[0]);
	return (i);
}
