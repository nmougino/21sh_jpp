/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 20:03:12 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/31 17:18:06 by nmougino         ###   ########.fr       */
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

/*
	Soit on split, puis on attribue. Ce qui semble plus simple.
	Soit on fait les deux.. Ce qui semble obligatoire.
*/

static char	*which_operator(char *cmdl)
{
	if (ft_strnequ(DLESS, cmdl, ft_strlen(DLESS)))
		return (DLESS);
	else if (ft_strnequ(DGREAT, cmdl, ft_strlen(DGREAT)))
		return (DGREAT);
	else if (ft_strnequ(LESSAND, cmdl, ft_strlen(LESSAND)))
		return (LESSAND);
	else if (ft_strnequ(GREATAND, cmdl, ft_strlen(GREATAND)))
		return (GREATAND);
	else if (ft_strnequ(AND_IF, cmdl, ft_strlen(AND_IF)))
		return (AND_IF);
	else if (ft_strnequ(OR_IF, cmdl, ft_strlen(OR_IF)))
		return (OR_IF);
	else if (ft_strnequ(PIPE, cmdl, ft_strlen(PIPE)))
		return (PIPE);
	else if (ft_strnequ(AMPERSAND, cmdl, ft_strlen(AMPERSAND)))
		return (AMPERSAND);
	else if (ft_strnequ(SEMI, cmdl, ft_strlen(SEMI)))
		return (SEMI);
	else if (ft_strnequ(LESS, cmdl, ft_strlen(LESS)))
		return (LESS);
	else if (ft_strnequ(GREAT, cmdl, ft_strlen(GREAT)))
		return (GREAT);
	return (NO_OP);
}

static int	lex_handle_quotes(char *cmdl)
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

static void	lex_define_prev_token(char **cmdl, int *j, t_list **lst)
{
	t_token	tok;

	tok.content = ft_strndup(*cmdl, (size_t)*j);
	tok.type = WORD;
	ft_lstadd_end(lst, ft_lstnew(&tok, sizeof(t_token)));
	*cmdl += *j;
	*j = 0;
}

static void	lex_define_op_token(char **cmdl, int *j, t_list **lst, enum e_token_type op)
{
	t_token	tok;

	tok.content = ft_strdup(which_operator(*cmdl));
	tok.type = op;
	ft_lstadd_end(lst, ft_lstnew(&tok, sizeof(t_token)));
	ft_printf("here we have : %d, w|%s| for |%s|\n", ft_strlen(which_operator(*cmdl)), which_operator(*cmdl), *cmdl);
	*cmdl += ft_strlen(which_operator(*cmdl));
	*j = 0;
}

static enum e_token_type	is_operator(char *cmdl)
{
	if (ft_strnequ(DLESS, cmdl, ft_strlen(DLESS)) ||
		ft_strnequ(DGREAT, cmdl, ft_strlen(DGREAT)) ||
		ft_strnequ(LESSAND, cmdl, ft_strlen(LESSAND)) ||
		ft_strnequ(GREATAND, cmdl, ft_strlen(GREATAND)) ||
		ft_strnequ(LESS, cmdl, ft_strlen(LESS)) ||
		ft_strnequ(GREAT, cmdl, ft_strlen(GREAT)))
		return (OP_REDIRECT);
	else if (ft_strnequ(AND_IF, cmdl, ft_strlen(AND_IF)) ||
		ft_strnequ(OR_IF, cmdl, ft_strlen(OR_IF)) ||
		ft_strnequ(PIPE, cmdl, ft_strlen(PIPE)) ||
		ft_strnequ(AMPERSAND, cmdl, ft_strlen(AMPERSAND)) ||
		ft_strnequ(SEMI, cmdl, ft_strlen(SEMI)))
		return (OP_CONTROL);
	return (WORD);
}

t_list		*sh_lexer(char *cmdl)
{
	t_list	*lst;
	int		j;

	j = 0;
	lst = NULL;
	while (cmdl[j])
	{
		if (ft_strchr(" \t", cmdl[j]) && !j) // si c'est un blanc, on avance
			++cmdl;
		else if (ft_strchr(" \t", cmdl[j]) && j) // si c'est un blanc, on select le token
			lex_define_prev_token(&cmdl, &j, &lst);
		else if (ft_strchr("\"'", cmdl[j])) // si c'est une quote on gere
			j += lex_handle_quotes(cmdl + j);
		else if (j && ft_isdigit(cmdl[j]) && ft_strchr("<>", cmdl[j + 1])) // si c'est un io number on gere le precedent
			lex_define_prev_token(&cmdl, &j, &lst);
		else if (!j && ft_isdigit(cmdl[j]) && ft_strchr("<>", cmdl[j + 1])) // si c'est un io nombur on le passe en token
			lex_define_op_token(&cmdl, &j, &lst, IO_NUMBER);
		else if (j && is_operator(cmdl + j))
			lex_define_prev_token(&cmdl, &j, &lst);
		else if (!j && is_operator(cmdl + j))
			lex_define_op_token(&cmdl, &j, &lst, is_operator(cmdl + j));
		else
			++j;
		ft_printf("lexer iteration, j = %d, cmdl[j] = %d (%c).\n", j, cmdl[j], cmdl[j]);
	}
	if (j)
		lex_define_prev_token(&cmdl, &j, &lst);
	ft_printf("fin du lexer\n");
	return (lst);
}
