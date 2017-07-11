/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 11:32:08 by nmougino          #+#    #+#             */
/*   Updated: 2017/07/11 18:43:57 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		merge_cmdl(t_cmdl *tmp, t_cmdl *cmdl)
{
	if (tmp->cmdl)
	{
		if (!cmdl->cmdl)
			cmdl->cmdl = ft_strdup(tmp->cmdl);
		else
		{
			ft_stradd(&(cmdl->cmdl), "\n");
			ft_stradd(&(cmdl->cmdl), tmp->cmdl);
		}
		ft_strdel(&(tmp->cmdl));
		tmp->pos = 0;
	}
}

static void		quote_act(char *cmdl, int i, int *q)
{
	if (!*q && cmdl[i] == '\'')
		*q = 1;
	else if (!*q && cmdl[i] == '"')
		*q = 2;
	else if (!*q && cmdl[i] == '|' && !(cmdl[i + 1]))
		*q = 3;
	else if (cmdl[i] == '\'' && *q == 1)
		*q = 0;
	else if (cmdl[i] == '"' && *q == 2)
		*q = 0;
}

static int		quotes_scan(t_cmdl *cmdl)
{
	int	q;
	int	i;

	i = -1;
	q = 0;
	while (cmdl->cmdl[++i])
	{
		if (i && ft_strchr("\'\"|", cmdl->cmdl[i]) && cmdl->cmdl[i - 1] == '\\')
			continue ;
		else
			quote_act(cmdl->cmdl, i, &q);
	}
	if (q == 1)
		g_meta.prompt = "quote > ";
	else if (q == 2)
		g_meta.prompt = "dquote > ";
	else if (q == 3)
		g_meta.prompt = "pipe > ";
	return (q);
}

void			handle_quotes(t_cmdl *cmdl)
{
	t_cmdl		tmp;

	tmp.cmdl = NULL;
	tmp.pos = 0;
	while (quotes_scan(cmdl))
	{
		g_meta.gcmdl_f(&tmp);
		g_meta.prompt = g_meta.prompt_save;
		if (!tmp.cmdl)
		{
			sh_cmdl_init(cmdl);
			break ;
		}
		merge_cmdl(&tmp, cmdl);
	}
}
