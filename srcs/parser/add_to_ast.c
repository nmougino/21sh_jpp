/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 17:16:45 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/22 18:49:29 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** cette fonction ajoute un noeud en plein milieux de l'arbre, puisque cur
** n'est pas vide.
*/

void		middle_add_ast(t_btree **cur, t_btree **root,
					int i, t_list **tok)
{
	t_btree	*bttab[3];
	t_list	*simple;
	t_list	*token;

	(bttab[0]) = ft_btree_find_parent(*root, *cur);
	simple = *tok;
	while (--i > 0)
		simple = simple->next;
	token = simple->next;
	simple->next = NULL;
	simple = *tok;
	*tok = token->next;
	token->next = NULL;
	(bttab[1]) = ft_btreenew(token);
	(bttab[2]) = (*cur);
	while ((bttab[2])->right)
		(bttab[2]) = (bttab[2])->right;
	ft_btree_add(ft_btreenew(simple), (bttab[2]), RIGHT);
	ft_btree_add(*cur, bttab[1], LEFT);
	*cur = (bttab[1]);
	if (bttab[0])
		ft_btree_add(bttab[1], bttab[0], RIGHT);
	else
		*root = (bttab[1]);
}

/*
** meme que la precedente, mais ecrit dans un espace deja innocupe
*/

void		add_ast(t_btree **cur, int i, t_list **tok)
{
	t_list	*simple;
	t_list	*token;

	simple = *tok;
	while (--i > 0)
		simple = simple->next;
	token = simple->next;
	simple->next = NULL;
	simple = *tok;
	*tok = token->next;
	token->next = NULL;
	*cur = ft_btreenew(token);
	ft_btree_add(ft_btreenew(simple), *cur, LEFT);
}

void		add_simple_ast(t_btree **cur, int i, t_list **tok)
{
	t_list	*simple;

	simple = *tok;
	while (--i > 0)
		simple = simple->next;
	simple->next = NULL;
	simple = *tok;
	*cur = ft_btreenew(simple);
}
