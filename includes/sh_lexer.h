/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 20:14:37 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/09 22:24:20 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SH_LEXER_H
# define SH_LEXER_H

# include "shell.h"

enum		e_lexer_sate {
	STATE_GENERAL,
	STATE_ESCSEQ,
	STATE_SEP, // > >> < << | || & &&
	STATE_QUOTE,
	STATE_DQUOTE
};

enum		e_char_types {
	CT_GENERAL = 1,
	CT_PIPE = '|',
	CT_AMPERSAND = '&',
	CT_QUOTE = '\'',
	CT_DQUOTE = '"',
	CT_ESCAPESEQ = '\\',
	CT_SEMICOLON = ';',
	CT_WHITESPACE = ' ',
	CT_GREATER = '>',
	CT_LESSER = '<'
};

# define DEF_TOK define_token(&lst, j, cmdl + i - j)

t_list		*sh_lexer(char *cmdl);

#endif
