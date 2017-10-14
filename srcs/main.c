/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:34:57 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/14 23:02:49 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_meta	g_meta;

void		sh_cmdl_init(t_cmdl *cmdl)
{
	if (cmdl->cmdl && !HISTO.is_in)
		ft_strdel(&(cmdl->cmdl));
	cmdl->pos = 0;
}

static void	del_tokens(void *elem, size_t s)
{
	t_token	*tok;

	tok = (t_token*)elem;
	free(tok->content);
	free(tok);
	(void)s;
}

void		del_ast(void *d)
{
	ft_lstdel((t_list **)&d, del_tokens);
}

int			exec_mother(t_cmdl *cmdl)
{
	t_list	*tokens;

	if (cmdl->cmdl && cmdl->cmdl[0] &&
		syntax_check((tokens = cmdl_treatment(cmdl))))
	{
		if ((g_meta.ast = ast_parser(tokens)))
		{
			ft_btreemap(&g_meta.ast, hd_parser);
			exec_ast(g_meta.ast);
			ft_btreedel(&g_meta.ast, del_ast);
		}
		else
			ft_lstdel(&tokens, del_tokens);
	}
	else if (cmdl->cmdl && cmdl->cmdl[0])
		ft_lstdel(&tokens, del_tokens);
	return (1);
}

int			main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	mapsigs();
	g_meta.cmdl.cmdl = NULL;
	g_meta.cmdl.pos = 0;
	metainit(env);
	while (true)
	{
		if (!get_cmdl(&(g_meta.cmdl)))
			break ;
		g_meta.exec = 1;
		if (!exec_mother(&(g_meta.cmdl)))
			break ;
		g_meta.exec = 0;
		sh_cmdl_init(&(g_meta.cmdl));
	}
	g_meta.shenv ? ft_lstdel(&(g_meta.shenv), env_del)
		: ft_lstdel(&(g_meta.shenv_save), env_del);
	destroy_history();
	if (g_meta.clipbo)
		free(g_meta.clipbo);
	ft_putendl("exit bye xo");
	return (0);
}
