/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:46:11 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/22 19:31:38 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	prout(int rip, t_pre_exec *pre, t_btree *nr, int *fd)
{
	int	ibi;

	clodup(fd, 0);
	if (rip)
		exit(ft_launch_pipeline(nr, nr->parent->parent->right));
	else
	{
		handle_redir(&(pre->com), NULL);
		if ((ibi = is_builtin(pre->com.com_name)))
			exit(exec_builtin_pipe(&(pre->com), ibi - 1, pre->env));
		exec_simple(pre->com.i, &(pre->com), pre->env);
	}
}

int		ft_pipe_to_right(int *fd, t_btree *node_right)
{
	int			rip;
	t_pre_exec	pre;
	pid_t		pid_right;
	int			status_right;

	status_right = CMD_FAIL;
	if (!(rip = (node_right->parent->parent && ((t_token *)(((t_list *)
	(node_right->parent->parent->data))->content))->type == OP_CONTROL)))
		prepare_exec(&pre, node_right);
	if (!(pid_right = ft_fork("sh")))
		prout(rip, &pre, node_right, fd);
	else if (pid_right > 0)
	{
		close(fd[1]);
		waitpid(pid_right, &status_right, 0);
		if (!rip)
			close_exec(&pre);
	}
	return (status_right);
}

int		ft_launch_pipeline(t_btree *node_left, t_btree *node_right)
{
	int			fd[2];
	int			status_right;
	pid_t		pid_left;
	t_pre_exec	pre;

	status_right = CMD_FAIL;
	if (pipe(fd) == -1)
		return (ft_dprintf(2, "sh: pipe failed\n") ? CMD_FAIL : CMD_FAIL);
	prepare_exec(&pre, node_left);
	if (!(pid_left = ft_fork("sh")))
	{
		clodup(fd, 1);
		handle_redir(&(pre.com), NULL);
		if ((pid_left = is_builtin(pre.com.com_name)))
			exit(exec_builtin_pipe(&(pre.com), pid_left - 1, pre.env));
		exec_simple(pre.com.i, &(pre.com), pre.env);
	}
	else if (pid_left > 0)
	{
		status_right = ft_pipe_to_right(fd, node_right);
		close(fd[0]);
		waitpid(pid_left, NULL, 0);
	}
	close_exec(&pre);
	return (status_right ? CMD_FAIL : CMD_SUCCESS);
}

int		apply_pipe(t_btree *r)
{
	if (!r->left)
		return (ft_launch_pipeline(r, r->parent->right));
	else
		return (apply_pipe(r->left));
}
