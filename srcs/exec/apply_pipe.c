/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:46:11 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/16 19:54:18 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		do_so(t_btree *r, t_btree *tar, int (*f)(t_btree *, t_com *,
				void *, char **), void *tfd)
{
	t_com	com;
	int		i;
	char	**env;

	env = env_conv();
	create_simple(&com, (t_list *)(tar->data));
	i = f(r, &com, tfd, env);
	com_del(&com);
	ft_arrdel((void***)&env);
	return (i);
}

static int		pipe_right(t_btree *r, t_com *com, void *t, char **env)
{
	pid_t	pid;
	pid_t	pid_left;
	int		save[3];


	handle_redir(NULL, save);
	if (!(pid = ft_fork("sh")))
	{
		clodup(((int **)t)[0], 0);
		clodup(((int **)t)[1], 1);
		handle_redir(com, NULL);
		if ((pid = is_builtin(com->com_name)))
			exit(exec_builtin_pipe(com, pid - 1, env));
		exec_simple(com->i, com, env);
	}
	else if (pid != -1)
	{
		ft_lstadd_end(&g_meta.pids, ft_lstnew(&pid, sizeof(int)));
		pid_left = pipe_left(r, ((int **)t)[0], com->heredoc);
		restore_redir(save);
		(((int **)t)[1]) ? close(((int **)t)[1][1]) : 0;
	}
	return (CMD_SUCCESS);
}

int				apply_pipe(t_btree *r, int *pfd)
{
	int	fd[2];
	int i;
	int	*tfd[2];

	tfd[0] = fd;
	tfd[1] = pfd;
	if (pipe(fd) == -1)
		return (ft_dprintf(2, "sh: pipe failed\n") ? -1 : -1);
	i = do_so(r, r->right, pipe_right, tfd);
	return (i);
}
