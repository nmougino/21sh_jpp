/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 17:25:13 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/22 19:22:07 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	do_fork(t_com *com, char **env, int *save)
{
	pid_t	pid;
	int		i;

	i = CMD_SUCCESS;
	if ((pid = ft_fork("sh")) == -1)
		return (CMD_FAIL);
	else if (pid > 0)
	{
		write_hd(com, save);
		waitpid(pid, &i, 0);
	}
	else if (!pid)
	{
		if (com->heredoc)
			clodup(com->hdfd, 0);
		exec_simple(com->i, com, env);
	}
	return (i ? CMD_FAIL : CMD_SUCCESS);
}

static int	launch_simple(t_btree *r)
{
	int		j;
	t_com	com;
	char	**env;
	int		save[3];

	env = env_conv();
	create_simple(&com, (t_list *)(r->data));
	handle_redir(&com, save);
	if (com.heredoc)
		pipe(com.hdfd);
	if (is_builtin(com.com_name))
		return (exec_builtin(&com, is_builtin(com.com_name) - 1, env, save));
	j = do_fork(&com, env, save);
	com_del(&com);
	ft_arrdel((void***)&env);
	if (!com.heredoc)
		restore_redir(save);
	return (!j ? CMD_SUCCESS : CMD_FAIL);
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
