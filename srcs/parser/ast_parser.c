/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 22:56:49 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/06 16:51:52 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"



/*

Lorsque le parser tombe sur un operateur de controle, il doit decider de le
placer sur une branche du noeud courant, ou d'en faire un noeud dont la branche
de gauche sera le noeud courant.

test - d 2> /dev/null && cat $FIC | wc -l || echo "/sw inexistant"

						 || (pri2 - pos2)
					   /    \
		(pri2 - pos1) &&     echo "/sw inexistant"
					/    \
test - d 2> /dev/null     | (pri1)
						/   \
				cat $FIC	 wc -l

echo "prout" | cat -e | lolcat

						|
					|		lolcat
	echo "prout"		cat -e
*/

/*

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
		if (priority_cmp(((t_token*)(((t_list*)((*cur)->data))->content))->content, tok))
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

/*
** cette fonction ajoute un noeud en plein milieux de l'arbre, puisque cur
** n'est pas vide.
*/

static void	middle_add_ast(t_btree **cur, t_btree **root, int i, t_list **tok)
{
	t_btree	*parent;
	t_btree	*new;
	t_list	*simple;
	t_list	*token;

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
	(*cur)->right = ft_btreenew(simple);
	new->left = *cur;
	*cur = new;
	if (parent)
		parent->right = new;
	else
		*root = new;
}

/*
** meme que la precedente, mais ecrit dans un espace deja innocupe
*/

static void	add_ast(t_btree **cur, int i, t_list **tok)
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

static void	add_simple_ast(t_btree **cur, int i, t_list **tok)
{
	t_list	*simple;

	simple = *tok;
	while (--i > 0)
		simple = simple->next;
	simple->next = NULL;
	simple = *tok;
	*cur = ft_btreenew(simple);
}

t_btree	*ast_parser(t_list *tok)
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
		while (lst && ((t_token*)(lst->content))->type != OP_CONTROL)
		{
			++i;
			lst = lst->next;
		}
		if (lst && ((t_token*)(lst->content))->type == OP_CONTROL)
		{
			cur = find_cur(&root, ((t_token*)(lst->content))->content); // determine le neoeud dans le quel ecrire.
			if (*cur)
				middle_add_ast(cur, &root, i, &tok);
			else
				add_ast(cur, i, &tok);
			i = 0;
		}
	}
	if (i)
	{
		cur = find_rem_cur(&root); // determine le neoeud dans le quel ecrire.
		add_simple_ast(cur, i, &tok);
	}
	return (root);
}

/*
** Ajoute les commandes precedentes a l'ast.
*/

// static void	ast_add_left(t_list *tok, int i, t_btree *ast)
// {
// 	t_list	*lst;
//
// 	lst = tok;
// 	while (i-- && lst->next)
// 		lst = lst->next;
// 	lst->next = NULL;
// 	while (ast->right)
// 		ast = ast->right;
// 	ast->left = ft_btreenew(lst);
// }
//
// static void	ast_add_control(t_list *tok, t_btree **ast)
// {
// 	t_btree	*new;
// 	t_btree	*cur;
//
// 	tok->next = NULL;
// 	new = ft_btreenew(tok);
// 	if (!(*ast))
// 		*ast = new;
// 	else
// 	{
// 		cur = *ast;
// 		while (cur->right)
// 			cur = cur->right;
// 		cur->right = new;
// 	}
// }
//
// /*
// ** le parser separe la ligne de commande et la transforme en arbre.
// ** les deux equivalent a un operateur de controle,
// ** les feuilles a une commande simple
// ** le contenu des feuilles sera un tableau de tokens. Normalement.
// */
//
// t_btree	*ast_parser(t_list *tok)
// {
// 	t_btree	*ast;
// 	t_list	*tmp;
// 	t_list	*cur;
// 	int		i;
//
// 	i = 0;
// 	ast = NULL;
// 	tmp = tok;
// 	while (tmp)
// 	{
// 		ft_printf("ici\n");
// 		if (((t_token *)(tmp->content))->type == OP_CONTROL)
// 		{
// 			ft_printf("fleur\n");
// 			cur = tmp->next;
// 			ast_add_control(tmp, &ast);
// 			ast_add_left(tok, i, ast);
// 			i = 0;
// 			tok = cur;
// 		}
// 		++i;
// 		tmp = tmp->next;
// 	}
// 	if (i && ast)
// 		ast_add_left(tok, i, ast);
// 	else if (i)
// 		ast = ft_btreenew(tok);
// 	return (ast);
// }
