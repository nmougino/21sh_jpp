/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 18:33:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/09 22:44:51 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Analyse sytaxique de la ligne de commande et divisions en tokens via
** la methode de l'automate a pile.
*/

static int	get_char_type(char c)
{
	if (!c || ft_strchr(" |&\\\'\"\t\n><", (int)c))
		return (c);
	return (CT_GENERAL);
}

static void	define_token(t_list **lst, int j, char *cmdl)
{
	char	*tmp;

	if ((tmp = ft_strsub(cmdl, 0, (size_t)j)))
	{
		ft_lstadd_end(lst, ft_lstnew(tmp, (size_t)j + 1));
		free(tmp);
	}
}

t_list		*sh_lexer(char *cmdl)
{
	t_list	*lst;
	int		ct;
	int		state;
	int		i;
	int		j;

	lst = NULL;
	i = 0;
	j = 0;
	state = STATE_GENERAL;
	while (cmdl[i])
	{
		ct = get_char_type(cmdl[i]);
		if (state == STATE_DQUOTE || state == STATE_QUOTE)
		{
			++j;
			if ((ct == CT_DQUOTE && state == STATE_DQUOTE) ||
				(ct == CT_QUOTE && state == STATE_QUOTE))
				state = STATE_GENERAL;
		}
		else if (state == STATE_SEP)
		{
			if (cmdl[i] == cmdl[i - 1] && j < 2)
				++j;
			else
			{
				ft_printf("fleur: |%s|\n", cmdl + i - j);
				DEF_TOK;
				--i;
				state = STATE_GENERAL;
				j = 0;
			}
		}
		else if (state == STATE_ESCSEQ)
			++j;
		else
		{
			if (ct == CT_PIPE || ct == CT_AMPERSAND || ct == CT_GREATER ||
				ct == CT_LESSER)
			{
				ft_printf("SEPARATOR DETECTED %d\n", j);
				if (j)
					DEF_TOK;
				j = 1;
				state = STATE_SEP;
			}
			else if (ct == CT_QUOTE && ++j)
				state = STATE_QUOTE;
			else if (ct == CT_DQUOTE && ++j)
				state = STATE_DQUOTE;
			else if (ct == CT_SEMICOLON)
			{
				if (j)
					DEF_TOK;
				define_token(&lst, 1, cmdl + i);
				j = 0;
			}
			else if (ct == CT_ESCAPESEQ && ++j)
				state = STATE_ESCSEQ;
			else if	(ct == CT_WHITESPACE)
			{
				ft_printf("WHITESPACE DETECTED %d\n", j);
				if (j)
					DEF_TOK;
				j = 0;
			}
			else
				++j;
		}
		++i;
	}
	if (j)
		DEF_TOK;
	return (lst);
}
