/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 20:03:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/12 20:33:45 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Le lexer va diviser la chaine.
** puis attribuer a chacun des maillons un type.
** Le contenu et le type formeront un token.
** La liste retournee par le lexer ira directement au departement
** "inhibiteurs et exapansions"
** Bisous.
*/

static int					lex_handle_quotes(char *cmdl)
{
	int		i;
	char	q;

	i = 1;
	q = *cmdl;
	while (cmdl[i])
	{
		if (cmdl[i] == q && cmdl[i - 1] != '\\')
		{
			++i;
			break ;
		}
		++i;
	}
	return (i);
}

static void					lex_handle_ionum(char **cmdl, int *j,
	t_list **lst)
{
	if (*j)
		lex_define_prev_token(cmdl, j, lst);
	else
		lex_define_ionum_token(cmdl, lst);
}

static void					lex_handle_operator(char **cmdl, int *j,
	t_list **lst)
{
	if (*j)
		lex_define_prev_token(cmdl, j, lst);
	else
		lex_define_op_token(cmdl, lst);
}

t_list						*sh_lexer(char *cmdl)
{
	t_list	*lst;
	int		j;

	j = 0;
	lst = NULL;
	while (cmdl[j])
	{
		if (ft_strchr(" \t\n", cmdl[j]) && !j)
			++cmdl;
		else if (ft_strchr(" \t", cmdl[j]) && j)
			lex_define_prev_token(&cmdl, &j, &lst);
		else if (ft_strchr("\"'", cmdl[j]))
			j += lex_handle_quotes(cmdl + j);
		else if (ft_strchr("012", cmdl[j]) && ft_strchr("<>", cmdl[j + 1]))
			lex_handle_ionum(&cmdl, &j, &lst);
		else if (is_operator(cmdl + j))
			lex_handle_operator(&cmdl, &j, &lst);
		else
			++j;
	}
	if (j)
		lex_define_prev_token(&cmdl, &j, &lst);
	return (lst);
}
