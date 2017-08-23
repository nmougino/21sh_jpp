/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:46:11 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/23 21:12:00 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static int	exec_pipe_left(t_btree *r, int *fd)
{
	int		i;
	pid_t	pid;
	t_com	com;
	char	**env;

	env = env_conv();
	i = create_simple(&com, (t_list *)(r->data));
	if (!(pid = ft_fork("sh")))
	{
		ft_printf("launching %s\n", com.com_name);
		close(fd[0]);
		dup2(fd[1], 1);
		exec_simple(i, &com, env);
	}
	else
	{
		waitpid(pid, &i, 0);
		ft_printf("fin %s\n", com.com_name);
		com_del(&com);
		ft_arrdel((void**)env);
		return (i);
	}
	return (CMD_FAIL);
}

static int	pipe_left(t_btree *r, int *fd)
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
		close(fd[1]);
		dup2(fd[0], 0);
		if (pfd)
		{
			ft_printf("proutCACACA\n", com.com_name);
			close(pfd[0]);
			dup2(pfd[1], 1);
		}
		ft_printf("launching %s\n", com.com_name);
		exec_simple(i, &com, env);
	}
	else
	{
		pipe_left(prev->left, fd);
		ft_printf("apres left\n", com.com_name);
		waitpid(pid, &i, 0);
		ft_printf("fin %s\n", com.com_name);
		com_del(&com);
		ft_arrdel((void**)env);
		return (i);
	}
	return (CMD_FAIL);
}

int			apply_pipe(t_btree *r, int *pfd)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (ft_dprintf(2, "sh: pipe failed\n") ? -1 : -1);
	return (pipe_right(r, r->right, fd, pfd));
}
