/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:46:11 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/22 20:53:31 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	pipe_launch_left(t_pre_exec *pre, int *fd)
{
	int	ibi;

	clodup(fd, 1);
	if (pre->com.heredoc)
		clodup(pre->com.hdfd, 0);
	handle_redir(&(pre->com), NULL);
	if ((ibi = is_builtin(pre->com.com_name)))
		exit(exec_builtin_pipe(&(pre->com), ibi - 1, pre->env));
	exec_simple(pre->com.i, &(pre->com), pre->env);
}

void	pipe_launch_right(int rip, t_pre_exec *pre, t_btree *nr, int *fd)
{
	int	ibi;

	clodup(fd, 0);
	if (pre->com.heredoc)
		clodup(pre->com.hdfd, 0);
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
	if (!(rip = (node_right->parent->parent && ft_strequ(((t_token *)(((t_list *)
	(node_right->parent->parent->data))->content))->content, "|"))))
		prepare_exec(&pre, node_right);
	if (!(pid_right = ft_fork("sh")))
		pipe_launch_right(rip, &pre, node_right, fd);
	else if (pid_right > 0)
	{
		if (!rip)
			write_hd(&(pre.com), pre.save);
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
		pipe_launch_left(&pre, fd);
	else if (pid_left > 0)
	{
		write_hd(&(pre.com), pre.save);
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
