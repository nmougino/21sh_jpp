/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 22:56:49 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/02 16:58:48 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Ajoute les commandes precedentes a l'ast.
*/

static void	ast_add_left(t_list *tok, int i, t_btree *ast)
{
	t_list	*lst;

	lst = tok;
	while (i-- && lst->next)
		lst = lst->next;
	lst->next = NULL;
	while (ast->right)
		ast = ast->right;
	ast->left = ft_btreenew(lst);
}

static void	ast_add_control(t_list *tok, t_btree **ast)
{
	t_btree	*new;
	t_btree	*cur;

	tok->next = NULL;
	new = ft_btreenew(tok);
	if (!(*ast))
		*ast = new;
	else
	{
		cur = *ast;
		while (cur->right)
			cur = cur->right;
		cur->right = new;
	}
}

/*
** le parser separe la ligne de commande et la transforme en arbre.
** les deux equivalent a un operateur de controle,
** les feuilles a une commande simple
** le contenu des feuilles sera un tableau de tokens. Normalement.
*/

t_btree	*ast_parser(t_list *tok)
{
	t_btree	*ast;
	t_list	*tmp;
	t_list	*cur;
	int		i;

	i = 0;
	ast = NULL;
	tmp = tok;
	while (tmp)
	{
		ft_printf("ici\n");
		if (((t_token *)(tmp->content))->type == OP_CONTROL)
		{
			ft_printf("fleur\n");
			cur = tmp->next;
			ast_add_control(tmp, &ast);
			ast_add_left(tok, i, ast);
			i = 0;
			tok = cur;
		}
		++i;
		tmp = tmp->next;
	}
	if (i && ast)
		ast_add_left(tok, i, ast);
	else if (i)
		ast = ft_btreenew(tok);
	return (ast);
}
