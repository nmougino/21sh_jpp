/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 17:25:13 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/22 20:49:37 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	exec_pipe(t_btree *r)
{
	(void)r;
	// int		i;
	// pid_t	pid;
	// int		fd[2];
	//
	// pipe(fd);
	// if (!(pid = fork()))
	// {
	//
	// }
	return (0);
}

static int	exec_op(t_btree *r)
{
	if (ft_strequ(((t_token *)(((t_list *)(r->data))->content))->content,
		PIPE))
		return(exec_pipe(r));
	return (-1);
}

int			exec_ast(t_btree *r)
{
	int		i;
	pid_t	pid;
	t_com	com;
	char	**env;

	i = ((t_token *)(((t_list *)(r->data))->content))->type;
	if (i == OP_CONTROL)
		return (exec_op(r));
	else
	{
		env = env_conv();
		i = create_simple(&com, (t_list *)(r->data));
		if (!(pid = fork()))
			exec_simple(i, &com, env);
		waitpid(pid, &i, 0);
		com_del(&com);
		ft_arrdel((void**)env);
		return (i);
	}
}
