/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 00:02:37 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/04 00:03:15 by nmougino         ###   ########.fr       */
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

int			apply_op(t_btree *r)
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