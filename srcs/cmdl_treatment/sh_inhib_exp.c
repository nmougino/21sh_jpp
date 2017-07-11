/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_inhib_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 06:18:46 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/12 01:02:55 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** IECD
** Inhibitors and Expansion Conversion Departement
*/

static void		replace_expansion(char **str, char *cont, int *i)
{
	char	*tmp;

	tmp = ft_strnew((size_t)*i + ft_strlen(cont) +
		ft_strlen(*str + (size_t)*i + ft_strlen(cont)));
	ft_strncpy(tmp, *str, (size_t)*i);
	ft_strcat(tmp, cont);
	ft_strcat(tmp, *str + (size_t)*i + ft_strlen(cont));
	ft_strdel(str);
	*str = tmp;
	*i += (int)ft_strlen(cont);
}

static void		handle_expansion(char **str, int *i)
{
	t_list	*tmp;
	size_t	len;

	len = ft_wordlen(*str + *i + 1);
	tmp = g_meta.shenv;
	while (tmp)
	{
		if (ft_strnequ(*str + *i + 1, ((t_shenv *)(tmp->content))->name,
			ft_strlen(((t_shenv *)(tmp->content))->name)))
		{
			replace_expansion(str, ((t_shenv *)(tmp->content))->cont, i);
			break ;
		}
		tmp = tmp->next;
	}
}

static void		quote_act(char c, int *q)
{
	if (!*q && c == '\'')
		*q = 1;
	else if (!*q && c == '"')
		*q = 2;
	else if (c == '\'' && *q == 1)
		*q = 0;
	else if (c == '"' && *q == 2)
		*q = 0;
}

void	sh_inhib_exp(t_list *lst)
{
	char	**str;
	int		q;
	int		i;

	str = (char **)(&lst->content);
	q = 0;
	i = -1;
	while ((*str)[++i])
	{
		if (ft_strchr("'\"", (*str)[i]))
		{
			quote_act((*str)[i--], &q);
			ft_move_left(*str + i);
		}
		else if ((*str)[i] == '\\')
			ft_move_left(*str + i);
		else if ((*str)[i] == '$' && (*str)[i + 1] &&
			!ft_strchr(" \n\t", (*str)[i + 1]))
			handle_expansion(str, &i);
	}
}
