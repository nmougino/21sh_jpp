/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_inhib_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 06:18:46 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/24 23:13:20 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** IECD
** Inhibitors and Expansion Conversion Departement
*/

void			replace_expansion(char **str, char *cont, size_t *i, char *name)
{
	char	*tmp;

	tmp = ft_strndup(*str, *i);
	ft_stradd(&tmp, cont);
	ft_stradd(&tmp, *str + *i + 1 + ft_strlen(name));
	ft_strdel(str);
	*str = tmp;
	*i += ft_strlen(cont);
}

static void		handle_tilde(char **str, size_t *i)
{
	char	*env;

	if ((env = get_env("HOME")))
		replace_expansion(str, env, i, "~");
}

static int		quote_act(char c, int *q)
{
	if (!*q && c == '\'')
		*q = 1;
	else if (!*q && c == '"')
		*q = 2;
	else if (c == '\'' && *q == 1)
		*q = 0;
	else if (c == '"' && *q == 2)
		*q = 0;
	else
		return (0);
	return (1);
}

void			sh_inhib_exp(t_list *lst)
{
	char	**str;
	int		q;
	size_t	i;

	if (((t_token *)(lst->content))->type != WORD)
		return ;
	q = 0;
	i = 0;
	str = &(((t_token *)(lst->content))->content);
	while ((*str)[i])
	{
		if (ft_strchr("'\"", (*str)[i]) && quote_act((*str)[i], &q))
			ft_move_left(*str + i--);
		else if ((*str)[i] == '\\')
			ft_move_left(*str + i);
		else if ((!q || q == 2) && (*str)[i] == '$' && (*str)[i + 1] &&
			!ft_strchr(" \n\t\"'$", (*str)[i + 1])
			&& !ft_isdigit((*str)[i + 1]))
			handle_expansion(str, &i);
		else if (!q && (*str)[i] == '~')
			handle_tilde(str, &i);
		++i;
	}
}
