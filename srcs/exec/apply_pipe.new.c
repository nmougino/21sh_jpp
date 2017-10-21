/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe.new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:46:11 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/21 18:27:20 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	prepare_exec(t_pre_exec *pre, t_btree *tar)
{
	pre->env = env_conv();
	create_simple(&(pre->com), (t_list *)(tar->data));
	handle_redir(NULL, pre->save);
}

static void	close_exec(t_pre_exec *pre)
{
	com_del(&(pre->com));
	ft_arrdel((void***)&(pre->env));
}

// static int	ft_pipe_to_right(int fd[2], t_ast *node_right)
// {
// 	pid_t	pid_right;
// 	int		status_right;
//
// 	if ((pid_right = fork()) == -1)
// 		ft_exit(STR_FORK_ERROR, 1);
// 	if (pid_right == 0)
// 	{
// 		close(fd[1]);
// 		ft_make_dup2(node_right->token->str, fd[0], STDIN_FILENO);
// 		if (node_right->parent->parent\
// 				&& node_right->parent->parent->operator_type == PIPE)
// 			exit(ft_launch_pipeline(node_right,\
// 						node_right->parent->parent->right));
// 		else
// 			exit(ft_launch_one_side(node_right));
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		waitpid(pid_right, &status_right, 0);
// 	}
// 	return (ft_exit_status(status_right));
// }
//
// static int	ft_pipe_to_right(int *fd, t_btree *node_right)
// {
// 	t_pre_exec	pre;
// 	pid_t		pid_right;
// 	int			status_right;
//
// 	prepare_exec(&pre, node_right);
// 	if (!(pid_left = ft_fork("sh")))
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDOUT_FILENO);
// 		if (node_right->parent->parent && (((t_token *)(((t_list *)
// 		(node_right->parent->parent->data))->content))->type == OP_CONTROL)
// 			exit(ft_launch_pipeline(node_right,\
// 						node_right->parent->parent->right));
// 		else
//
// 			exit(ft_launch_one_side(node_right));
// 	}
// 	return (CMD_FAIL);
// }

int	ft_pipe_to_right(int *fd, t_btree *node_right)
{
	int			rip;
	t_pre_exec	pre;
	pid_t		pid_right;
	int			status_right;

	status_right = CMD_FAIL;
	rip = (node_right->parent->parent && ((t_token *)(((t_list *)
	(node_right->parent->parent->data))->content))->type == OP_CONTROL);
	if (!rip)
		prepare_exec(&pre, node_right);
	if (!(pid_right = ft_fork("sh")))
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (rip)
			exit(ft_launch_pipeline(node_right,
				node_right->parent->parent->right));
		else
		{
			handle_redir(&(pre.com), NULL);
			if ((pid_right = is_builtin(pre.com.com_name)))
				exit(exec_builtin_pipe(&(pre.com), pid_right - 1, pre.env));
			exec_simple(pre.com.i, &(pre.com), pre.env);
		}
	}
	else if (pid_right > 0)
	{
		close(fd[1]);
		waitpid(pid_right, &status_right, 0);
		if (!rip)
			close_exec(&pre);
	}
	return (status_right);
}

int	ft_launch_pipeline(t_btree *node_left, t_btree *node_right)
{
	int			fd[2];
	pid_t		pid_left;
	int			status_right;
	t_pre_exec	pre;

	status_right = CMD_FAIL;
	if (pipe(fd) == -1)
		return (ft_dprintf(2, "sh: pipe failed\n") ? CMD_FAIL : CMD_FAIL);
	prepare_exec(&pre, node_left);
	if (!(pid_left = ft_fork("sh")))
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
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
	return (status_right);
}

int				apply_pipe(t_btree *r)
{
	if (!r->left)
		return (ft_launch_pipeline(r, r->parent->right));
	else
		return (apply_pipe(r->left));
}
