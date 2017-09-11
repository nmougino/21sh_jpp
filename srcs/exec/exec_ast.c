/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 17:25:13 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/11 19:07:06 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	launch_simple(t_btree *r)
{
	int		i;
	pid_t	pid;
	t_com	com;
	char	**env;
	int 	save[3];

	env = env_conv();
	i = create_simple(&com, (t_list *)(r->data));
	handle_redir(&com, save);
	if ((pid = is_builtin(com.com_name)))
		return (exec_builtin(&com, pid - 1, env, save));
	if ((pid = ft_fork("sh")) && pid != -1)
		waitpid(pid, &i, 0);
	else if (!pid)
		exec_simple(i, &com, env);
	com_del(&com);
	ft_arrdel((void***)&env);
	restore_redir(save);
	return (pid != -1 ? i : CMD_FAIL);
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
