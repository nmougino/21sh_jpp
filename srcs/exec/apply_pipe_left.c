/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:16:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/28 21:36:56 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		exec_pipe_left(t_com *com, int *tfd, char **env, char *hd)
{
	pid_t	pid;
	int		save[3];

	handle_redir(NULL, save);
	if (!(pid = ft_fork("sh")))
	{
		clodup(tfd, 1);
		handle_redir(com, NULL);
		if (hd)
			ft_putstr(hd);
		if (com->heredoc)
			clodup(com->hdfd, 0);
		if ((pid = is_builtin(com->com_name)))
			exit(exec_builtin_pipe(com, pid - 1, env));
		exec_simple(com->i, com, env);
	}
	else if (pid != -1)
	{
		write_hd(com, save);
		waitpid(pid, &pid, 0);
		restore_redir(save);
		close(tfd[1]);
	}
	return (pid);
}

int				pipe_left(t_btree *r, int *fd, char *hd)
{
	t_com	com;
	int		i;
	char	**env;

	if (((t_token *)(((t_list *)(r->left->data))->content))->type == OP_CONTROL)
		return (apply_pipe(r->left, fd));
	else
	{
		env = env_conv();
		create_simple(&com, (t_list *)(r->left->data));
		if (com.heredoc)
			pipe(com.hdfd);
		i = exec_pipe_left(&com, fd, env, hd);
		com_del(&com);
		ft_arrdel((void***)&env);
		return (i);
	}
}
