/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:46:11 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/24 07:36:11 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		exec_pipe_left(t_btree *r, int *fd)
{
	int		i;
	pid_t	pid;
	t_com	com;
	char	**env;
	// int		save[3];

	env = env_conv();
	create_simple(&com, (t_list *)(r->data));
	// handle_redir(NULL, save);
	if (!(pid = ft_fork("sh")))
	{
		clodup(fd, 1);
		handle_redir(&com, NULL);
		if ((pid = is_builtin(com.com_name)))
			exit(exec_builtin_pipe(&com, pid - 1, env));
		exec_simple(com.i, &com, env);
	}
	else
	{
		waitpid(pid, &i, 0);
		close(fd[1]);
		com_del(&com);
		ft_arrdel((void***)&env);
		// restore_redir(save);
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
	// int		save[3];

	env = env_conv();
	create_simple(&com, (t_list *)(r->data));
	// handle_redir(NULL, save);
	if (!(pid = ft_fork("sh")))
	{
		clodup(fd, 0);
		clodup(pfd, 1);
		handle_redir(&com, NULL);
		if ((pid = is_builtin(com.com_name)))
			exit(exec_builtin_pipe(&com, pid - 1, env));
		exec_simple(com.i, &com, env);
	}
	else if (pid != -1)
	{
		if (com.heredoc)
		{
			clodup(fd, 1);
			ft_putstr_fd(com.heredoc, fd[1]);
			close(fd[1]);
		}
		else
			pipe_left(prev->left, fd);
		waitpid(pid, &i, 0);
		if (pfd)
			close(pfd[1]);
		com_del(&com);
		ft_arrdel((void***)&env);
		// restore_redir(save);
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
	return (i);
}
