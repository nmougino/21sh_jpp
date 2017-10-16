/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 00:02:37 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/16 21:55:37 by nmougino         ###   ########.fr       */
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

static void		fdellol(void *p, size_t i)
{
	(void)i;
	free(p);
}

int			apply_op(t_btree *r)
{
	char	*tok;
	int		ret;

	ret = CMD_SUCCESS;
	tok = ((t_token *)(((t_list *)(r->data))->content))->content;
	if (ft_strequ(tok, AND_IF))
		return (apply_and_if(r));
	else if (ft_strequ(tok, OR_IF))
		return (apply_or_if(r));
	else if (ft_strequ(tok, SEMI))
		return (apply_semi(r));
	else if (ft_strequ(tok, PIPE) && !apply_pipe(r, NULL) && g_meta.pids)
	{
		waitpid(*(pid_t*)(g_meta.pids->content), &ret, 0);
		ft_lstrem(&g_meta.pids, g_meta.pids, fdellol);
		while (g_meta.pids)
		{
			kill(*(pid_t*)(g_meta.pids->content), SIGINT);
			ft_lstrem(&g_meta.pids, g_meta.pids, fdellol);
		}
		return (ret);
	}
	return (CMD_FAIL);
}
