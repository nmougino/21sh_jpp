/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:34:57 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/18 11:15:26 by nmougino         ###   ########.fr       */
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

void		sh_putast(t_btree *r, int l)
{
	t_list	*lst;
	if (r)
	{
		lst = ((t_list *)(r->data));
		ft_putstr("|");
		while (lst)
		{
			ft_putstr(((t_token *)(lst->content))->content);
			if (lst->next)
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

int		exec_mother(t_cmdl *cmdl)
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
	return (1);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_meta.cmdl.cmdl = NULL;
	g_meta.cmdl.pos = 0;
	metainit(env);
	while (true)
	{
		if (!get_cmdl(&(g_meta.cmdl)))
			break;
		if (!exec_mother(&(g_meta.cmdl)))
			break;
		sh_cmdl_init(&(g_meta.cmdl));
	}
	if (g_meta.shenv)
		ft_lstdel(&(g_meta.shenv), env_del);
	else
		ft_lstdel(&(g_meta.shenv_save), env_del);
	destroy_history();
	close(g_meta.fd);
	if (g_meta.clipbo)
		free(g_meta.clipbo);
	return (0);
}

/*


Probleme :
Il faut : soit remplacer le systeme de parse de l'ast pour convertir les commandes avant l'execution
			soit faire ca qu'avec les pipes

	ceci dans le but de gerer les heredocs en pipes...
	ca va saouler.
	donc

	le plus simple est de convertir toutes les commandes des le debut
		il va donc falloir mallocer les com
		adapter les fonctions d'executions
		bien freer...



*/
