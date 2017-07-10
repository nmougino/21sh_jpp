/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 18:33:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/10 02:09:23 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Analyse sytaxique de la ligne de commande et divisions en tokens via
** la methode de l'automate a pile.
*/

static int	get_char_type(char c)
{
	if (!c || ft_strchr(" |&\\\'\"\t\n><;", (int)c))
		return (c);
	return (CT_GENERAL);
}

void		define_token(t_list **lst, int j, char *cmdl)
{
	char	*tmp;

	if ((tmp = ft_strsub(cmdl, 0, (size_t)j)))
	{
		ft_lstadd_end(lst, ft_lstnew(tmp, (size_t)j + 1));
		free(tmp);
	}
}

static void	lex_wheel(t_lex *lex, char *cmdl)
{
	while (cmdl[lex->i])
	{
		lex->ct = get_char_type(cmdl[lex->i]);
		if (lex->state == STATE_DQUOTE || lex->state == STATE_QUOTE)
			lex_quotes(lex);
		else if (lex->state == STATE_SEP)
			lex_sep(lex, cmdl);
		else if (lex->ct == CT_PIPE || lex->ct == CT_ASAND ||
			lex->ct == CT_GREATER || lex->ct == CT_LESSER)
			lex_gen_sep(lex, cmdl);
		else if ((lex->ct == CT_QUOTE || lex->ct == CT_DQUOTE) && ++(lex->j))
			lex->state = lex->ct == CT_QUOTE ? STATE_QUOTE : STATE_DQUOTE;
		else if (lex->ct == CT_SEMICOLON)
			lex_gen_seco(lex, cmdl);
		else if (lex->ct == CT_ESCAPESEQ && (lex->j += 2))
			++(lex->i);
		else if	(lex->ct == CT_WHITESPACE)
			lex_gen_blank(lex, cmdl);
		else
			++(lex->j);
		if (cmdl[lex->i])
			++(lex->i);
	}
}

t_list		*sh_lexer(char *cmdl)
{
	t_lex	lex;

	lex.lst = NULL;
	lex.i = 0;
	lex.j = 0;
	lex.state = STATE_GENERAL;
	lex_wheel(&lex, cmdl);
	if (lex.j)
		define_token(&(lex.lst), lex.j, cmdl + lex.i - lex.j);
	return (lex.lst);
}
