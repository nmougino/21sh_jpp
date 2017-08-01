/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 22:56:49 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/01 23:08:46 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	int		i;

	i = 0;
	ast = NULL;
	tmp = tok;
	while (tmp)
	{
		if ((t_token *)(tmp->content)->type == OP_CONTROL)
		{
			ast_add_control(tmp);
			ast_add_left(tok, i);
			i = 0;
			tok = tmp->next;
		}
		++i;
		tmp = tmp->next;
	}
	return (ast);
}
