/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 17:25:13 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/23 16:18:25 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
//
// static void	exec_pipe_left(t_btree *r, int *fd)
// {
// 	if (((t_token *)(((t_list *)(r->data))->content))->type == OP_CONTROL)
// 		exec_pipe(r);
// 	else
//
// }
//
// static int	exec_pipe(t_btree *r)
// {
// 	int		fd[2];
// 	t_com	com;
// 	char	**env;
// 	int		i;
// 	pid_t	pid;
//
// 	i = create_simple(&com, (t_list *)(r->right->data));
// 	env = env_conv();
// 	pipe(fd);
// 	if ((pid = fork()))
// 	{
// 		dup2(fd[0], 0);
// 		close(fd[1]);
// 		exec_simple(i, &com, env);
// 	}
// 	exec_pipe_left(r->left, fd);
// 	waitpid(pid, &i, 0);
// 	com_del(&com);
// 	ft_arrdel((void**)env);
// 	close(fd[0]);
// 	close(fd[1]);
// 	return (i);
// }
//
// static int	exec_op(t_btree *r)
// {
// 	if (ft_strequ(((t_token *)(((t_list *)(r->data))->content))->content,
// 		PIPE))
// 		return(exec_pipe(r));
// 	return (-1);
// }
//
// int			exec_ast(t_btree *r)
// {
// 	int		i;
// 	pid_t	pid;
// 	t_com	com;
// 	char	**env;
//
// 	i = ((t_token *)(((t_list *)(r->data))->content))->type;
// 	if (i == OP_CONTROL)
// 		return (exec_op(r));
// 	else
// 	{
// 		env = env_conv();
// 		i = create_simple(&com, (t_list *)(r->data));
// 		if (!(pid = fork()))
// 			exec_simple(i, &com, env);
// 		waitpid(pid, &i, 0);
// 		com_del(&com);
// 		ft_arrdel((void**)env);
// 		return (i);
// 	}
// }

// ------------------------

static int	apply_and_if(t_btree *r)
{
	int	i;

	if ((i = exec_ast(r->left)) == CMD_SUCCESS)
		return (exec_ast(r->right));
	else
		return (i);
}

static int	apply_or_if(t_btree *r)
{
	int	i;

	if ((i = exec_ast(r->left)) != CMD_SUCCESS)
		return (exec_ast(r->right));
	else
		return (i);
}

static int	apply_semi(t_btree *r)
{
	exec_ast(r->left);
	return (exec_ast(r->right));
}

static int	apply_op(t_btree *r)
{
	char	*tok;

	tok = ((t_token *)(((t_list *)(r->data))->content))->content;
	if (ft_strequ(tok, AND_IF))
		return (apply_and_if(r));
	else if (ft_strequ(tok, OR_IF))
		return (apply_or_if(r));
	else if (ft_strequ(tok, SEMI))
		return (apply_semi(r));
	return (CMD_FAIL);
}

static int	launch_simple(t_btree *r)
{
	int		i;
	pid_t	pid;
	t_com	com;
	char	**env;

	env = env_conv();
	i = create_simple(&com, (t_list *)(r->data));
	if ((pid = fork()) == -1)
		return (-1);
	else if (pid)
	{
		waitpid(pid, &i, 0);
		com_del(&com);
		ft_arrdel((void**)env);
		return (i);
	}
	else
		exec_simple(i, &com, env);
	return (CMD_FAIL);
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
