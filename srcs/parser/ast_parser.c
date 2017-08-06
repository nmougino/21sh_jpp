/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 22:56:49 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/06 17:17:06 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Lorsque le parser tombe sur un operateur de controle, il doit decider de le
** placer sur une branche du noeud courant, ou d'en faire un noeud dont
** la branche de gauche sera le noeud courant.
**
** test - d 2> /dev/null && cat $FIC | wc -l || echo "/sw inexistant"
**
** 						 || (pri2 - pos2)
** 					   /    \
** 		(pri2 - pos1) &&     echo "/sw inexistant"
** 					/    \
** test - d 2> /dev/null     | (pri1)
** 						/   \
** 				cat $FIC	 wc -l
**
** echo "prout" | cat -e | lolcat
**
** 						|
** 					|		lolcat
** 	echo "prout"		cat -e
*/

static int		priority_cmp(char *cur, char *tok)
{
	int	p_cur;
	int	p_tok;

	if (ft_strequ(tok, AMPERSAND) || ft_strequ(tok, SEMI))
		p_tok = 2;
	else if (ft_strequ(tok, AND_IF) || ft_strequ(tok, OR_IF))
		p_tok = 1;
	else if (ft_strequ(tok, PIPE))
		p_tok = 0;
	else
		p_tok = -1;
	if (ft_strequ(cur, AMPERSAND) || ft_strequ(cur, SEMI))
		p_cur = 2;
	else if (ft_strequ(cur, AND_IF) || ft_strequ(cur, OR_IF))
		p_cur = 1;
	else if (ft_strequ(cur, PIPE))
		p_cur = 0;
	else
		p_cur = -1;
	return (p_cur > p_tok);
}

static t_btree	**find_cur(t_btree **root, char *tok)
{
	t_btree	**cur;

	if (!*root)
		return (root);
	cur = root;
	while (*cur)
	{
		if (priority_cmp(
			((t_token*)(((t_list*)((*cur)->data))->content))->content, tok))
			cur = &((*cur)->right);
		else
			return (cur);
	}
	return (cur);
}

static t_btree	**find_rem_cur(t_btree **root)
{
	t_btree	**cur;

	if (!*root)
		return (root);
	cur = root;
	while ((*cur))
		cur = &((*cur)->right);
	return (cur);
}

t_btree			*ast_parser(t_list *tok)
{
	t_btree	*root;
	t_btree	**cur;
	t_list	*lst;
	int		i;

	i = 0;
	root = NULL;
	lst = tok;
	while (lst)
	{
		lst = tok;
		while (lst && ((t_token*)(lst->content))->type != OP_CONTROL && ++i)
			lst = lst->next;
		if (lst && ((t_token*)(lst->content))->type == OP_CONTROL)
		{
			cur = find_cur(&root, ((t_token*)(lst->content))->content);
			*cur ? middle_add_ast(cur, &root, i, &tok) : add_ast(cur, i, &tok);
			i = 0;
		}
	}
	if (i)
		add_simple_ast(find_rem_cur(&root), i, &tok);
	return (root);
}
