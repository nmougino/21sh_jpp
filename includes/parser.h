/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:23:19 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/14 15:42:07 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shell.h"

/*
** add_to_ast.c
*/

void	middle_add_ast(t_btree **cur, t_btree **root,
			int i, t_list **tok);
void	add_ast(t_btree **cur, int i, t_list **tok);
void	add_simple_ast(t_btree **cur, int i, t_list **tok);

/*
**ast_parser.c
*/

t_btree	*ast_parser(t_list *tok);

#endif
