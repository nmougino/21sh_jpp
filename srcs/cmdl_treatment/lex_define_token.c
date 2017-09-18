/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_define_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 21:13:06 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/18 10:55:48 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lex_define_prev_token(char **cmdl, int *j, t_list **lst)
{
	t_token	tok;

	tok.content = ft_strndup(*cmdl, (size_t)(*j));
	tok.type = WORD;
	ft_lstadd_end(lst, ft_lstnew(&tok, sizeof(t_token)));
	*cmdl += *j;
	*j = 0;
}

void	lex_define_ionum_token(char **cmdl, t_list **lst)
{
	t_token	tok;

	tok.content = ft_strndup(*cmdl, 1);
	tok.type = IO_NUMBER;
	ft_lstadd_end(lst, ft_lstnew(&tok, sizeof(t_token)));
	*cmdl += 1;
}

void	lex_define_op_token(char **cmdl, t_list **lst)
{
	t_token	tok;

	tok.content = ft_strdup(which_operator(*cmdl));
	tok.type = is_operator(*cmdl);
	ft_lstadd_end(lst, ft_lstnew(&tok, sizeof(t_token)));
	*cmdl += ft_strlen(which_operator(*cmdl));
}
