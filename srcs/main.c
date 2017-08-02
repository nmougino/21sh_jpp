/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:34:57 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/02 17:00:47 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
	toujours un probleme dans le retour historique d'une commande sur plusieurs lignes
	Ajouter la verification termcaps
*/

/*
** penser a remplacer les ansi escape sequences par des termcap
** ajouter fonction e check des termcaps pour decider de leur activation
** creer un mode de get_cmdl minishell
*/

/*
	double free en CTRL D en parcours d'historique
*/

t_meta	g_meta;

void	sh_cmdl_init(t_cmdl *cmdl)
{
	if (cmdl->cmdl && !HISTO.is_in)
		ft_strdel(&(cmdl->cmdl));
	cmdl->pos = 0;
}

// static void	put_someshit(t_list *lst)
// {
// 	ft_printf(" |%s|\n", lst->content);
// }

// static void	del_someshit(void *elem, size_t s)
// {
// 	t_token	*tok;
//
// 	tok = (t_token*)elem;
// 	free(tok->content);
// 	free(tok);
// 	(void)s;
// }

static void	sh_putast(t_btree *r, int l)
{
	t_list	*lst;
	if (r)
	{
		lst = ((t_list *)(r->data));
		ft_putstr("|");
		while (lst)
		{
			ft_putstr(((t_token *)(lst->content))->content);
			ft_putstr(" ");
			lst = lst->next;
		}
		ft_putendl("|");
		if (r->left)
		{
			ft_printf("%*c|-left--: ", (l + 1) * 2, ' ');
			sh_putast(r->left, l + 1);
		}
		if (r->right)
		{
			ft_printf("%*c|-right-: ", (l + 1) * 2, ' ');
			sh_putast(r->right, l + 1);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_cmdl	cmdl;
	t_list	*tokens;
	t_btree	*ast;

	(void)ac;
	(void)av;
	cmdl.cmdl = NULL;
	cmdl.pos = 0;
	metainit(env);
	while (true)
	{
		if (!get_cmdl(&cmdl))
			break;
		tokens = cmdl_treatment(&cmdl);
		// ft_lstiter(tokens, put_someshit);
		ast = ast_parser(tokens);
		sh_putast(ast, 0);
		// ft_lstdel(&tokens, del_someshit);
		sh_cmdl_init(&cmdl);
	}
	ft_lstdel(&(g_meta.shenv), env_del);
	destroy_history();
	close(g_meta.fd);
	if (g_meta.clipbo)
		free(g_meta.clipbo);
	// ft_printf((char*)2);
	return (0);
}
