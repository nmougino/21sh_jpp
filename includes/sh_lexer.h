/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 20:14:37 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/12 05:29:01 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXER_H
# define SH_LEXER_H

# include "shell.h"

enum			e_lexer_sate {
	STATE_GENERAL,
	STATE_SEP,
	STATE_QUOTE,
	STATE_DQUOTE
};

enum			e_char_types {
	CT_GENERAL = 1,
	CT_PIPE = '|',
	CT_ASAND = '&',
	CT_QUOTE = '\'',
	CT_DQUOTE = '"',
	CT_ESCAPESEQ = '\\',
	CT_SEMICOLON = ';',
	CT_WHITESPACE = ' ',
	CT_GREATER = '>',
	CT_LESSER = '<'
};

# define DEF_TOK define_token(&(lex->lst), lex->j, cmdl + lex->i - lex->j)

typedef struct	s_lex
{
	t_list		*lst;
	int			ct;
	int			state;
	int			i;
	int			j;
}				t_lex;

t_list			*sh_lexer(char *cmdl);

void			define_token(t_list **lst, int j, char *cmdl);

void			lex_quotes(t_lex *lex);
void			lex_sep(t_lex *lex, char *cmdl);
void			lex_gen_sep(t_lex *lex, char *cmdl);
void			lex_gen_seco(t_lex *lex, char *cmdl);
void			lex_gen_blank(t_lex *lex, char *cmdl);

#endif
