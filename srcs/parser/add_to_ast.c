/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 17:16:45 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/14 20:55:11 by nmougino         ###   ########.fr       */
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
	t_btree	*parent;
	t_btree	*new;
	t_list	*simple;
	t_list	*token;
	t_btree	*tmp;

	parent = ft_btree_find_parent(*root, *cur);
	simple = *tok;
	while (--i > 0)
		simple = simple->next;
	token = simple->next;
	simple->next = NULL;
	simple = *tok;
	*tok = token->next;
	token->next = NULL;
	new = ft_btreenew(token);
	tmp = (*cur);
	while(tmp->right)
		tmp = tmp->right;
	tmp->right = ft_btreenew(simple);
	new->left = *cur;
	*cur = new;
	parent ? (parent->right = new) : (*root = new);
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
	(*cur)->left = ft_btreenew(simple);
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
