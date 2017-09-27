/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:46:11 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/27 22:28:33 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
	Bien..
	Premierement le travail de creation de commande est globalement le meme pour
	chaque operation, on peux les condenser en une seule fonction.
	Cela permetra de gere les pipes en amont.
	ensuite, je propose de gerer les heredocs avant le pipe de gauche mais pas
	differement

	apparement le comportement de bash est d'ecraser le cannal de lecture et
	de le remplacer par celui de sortie du heredoc, je trouve cela plus
	facile.

	Cependant je n'aime pas l'idee de melanger les pipes...
*/

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
		if ((pid = is_builtin(com->com_name)))
			exit(exec_builtin_pipe(com, pid - 1, env));
		exec_simple(com->i, com, env);
	}
	else if (pid != -1)
	{
		waitpid(pid, &pid, 0);
		restore_redir(save);
		close(tfd[1]);
	}
	return (pid);
}

static int		pipe_left(t_btree *r, int *fd, char *hd)
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
		i = exec_pipe_left(&com, fd, env, hd);
		com_del(&com);
		ft_arrdel((void***)&env);
		return (i);
	}
}

static int		pipe_right(t_btree *r, t_com *com, void *t, char **env)
{
	pid_t	pid;
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
		pipe_left(r, ((int **)t)[0], com->heredoc);
		waitpid(pid, &pid, 0);
		restore_redir(save);
		if (((int **)t)[1])
			close(((int **)t)[1][1]);
	}
	return (pid);
}

// static int		pipe_right(t_btree *r, t_com *com, void *t, char **env)
// {
// 	pid_t	pid;
// 	int		*src;
// 	int		save[3];
//
// 	handle_redir(NULL, save);
// 	src = com->heredoc ? com->hdfd : ((int **)t)[0];
// 	if (!(pid = ft_fork("sh")))
// 	{
// 		LOG("lancement commande right\n");
// 		clodup(src, 0);
// 		clodup(((int **)t)[1], 1);
// 		handle_redir(com, NULL);
// 		if ((pid = is_builtin(com->com_name)))
// 			exit(exec_builtin_pipe(com, pid - 1, env));
// 		exec_simple(com->i, com, env);
// 	}
// 	else if (pid != -1)
// 	{
// 		LOG("process parent...\n");
// 		if (com->heredoc)
// 		{
// 			LOG("injection heredoc...\n");
// 			clodup(src, 1);
// 			ft_putstr(com->heredoc);
// 			ft_putstr("COUCOU\n");
// 			restore_redir(save);
// 			close(src[1]);
// 			// src = ((int **)t)[0];
// 			LOG("hd done\n");
// 		}
// 		else
// 			pipe_left(r, src);
// 		LOG("Waitpid...\n");
// 		waitpid(pid, &pid, 0);
// 		LOG("waitpid done\n");
// 		restore_redir(save);
// 		if (((int **)t)[1])
// 			close(((int **)t)[1][1]);
// 	}
// 	return (pid);
// }

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
	LOG("FINIT\n");
	return (i);
}
