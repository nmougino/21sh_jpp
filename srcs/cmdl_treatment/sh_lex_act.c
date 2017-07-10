/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lex_act.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 01:43:48 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/10 01:44:09 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lex_quotes(t_lex *lex)
{
	++(lex->j);
	if ((lex->ct == CT_DQUOTE && lex->state == STATE_DQUOTE) ||
		(lex->ct == CT_QUOTE && lex->state == STATE_QUOTE))
		lex->state = STATE_GENERAL;
}

void	lex_sep(t_lex *lex, char *cmdl)
{
	if (cmdl[lex->i] == cmdl[lex->i - 1] && lex->j < 2)
		++(lex->j);
	else
	{
		DEF_TOK;
		--(lex->i);
		lex->state = STATE_GENERAL;
		lex->j = 0;
	}
}

void	lex_gen_sep(t_lex *lex, char *cmdl)
{
	if (lex->j)
		DEF_TOK;
	lex->j = 1;
	lex->state = STATE_SEP;
}

void	lex_gen_seco(t_lex *lex, char *cmdl)
{
	if (lex->j)
		DEF_TOK;
	define_token(&(lex->lst), 1, cmdl + lex->i);
	lex->j = 0;
}

void	lex_gen_blank(t_lex *lex, char *cmdl)
{
	if (lex->j)
		DEF_TOK;
	lex->j = 0;
}
