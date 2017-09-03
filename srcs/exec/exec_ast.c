/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 17:25:13 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/03 22:29:21 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	else if (ft_strequ(tok, PIPE))
		return (apply_pipe(r, NULL));
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
	if ((pid = is_builtin(com.com_name)))
		return (exec_builtin(&com, pid - 1, env));
	if ((pid = fork()) == -1)
		return (CMD_FAIL);
	else if (pid)
	{
		waitpid(pid, &i, 0);
		com_del(&com);
		ft_arrdel((void***)&env);
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
