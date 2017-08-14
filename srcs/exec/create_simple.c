/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 18:15:19 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/15 00:10:12 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	com_init(t_com *com)
{
	com->cmd_path = NULL;
	com->cmd_args = NULL;
	ft_bzero(&(com->fd), sizeof(int) * 3);
	ft_bzero(&(com->to_close), sizeof(int) * 3);
}

static t_list	*go_to_after_name(t_list *lst)
{
	while (lst && ((((t_token*)(lst->content))->type) != WORD))
	{
		if ((((t_token*)(lst->content))->type) > IO_NUMBER)
			lst = lst->next;
		lst = lst->next;
	}
	if (lst)
		lst = lst->next;
	return (lst);
}

static char	**create_args_tab(t_list *lst, size_t len)
{
	char	**ans;


	ans = malloc(sizeof(char*) * (len + 1));
	ans[len] = NULL;
	len = 0;
	while (lst)
	{
		if ((((t_token*)(lst->content))->type) == WORD)
			ans[len++] = ft_strdup(((t_token*)(lst->content))->content);
		else if ((((t_token*)(lst->content))->type) > IO_NUMBER)
			lst = lst->next;
		lst = lst->next;
	}
	return (ans);
}

static char	**get_cmd_args(t_list *lst)
{
	size_t	len;
	t_list	*cur;

	len = 0;
	lst = go_to_after_name(lst);
	cur = lst;
	while (cur)
	{
		if ((((t_token*)(cur->content))->type) == WORD)
			++len;
		else if ((((t_token*)(cur->content))->type) > IO_NUMBER)
			cur = cur->next;
		cur = cur->next;
	}
	return (create_args_tab(lst, len));
}

static void	prout(char **str)
{
	ft_putendl(*str);
}

int			create_simple(t_com *com, t_list *lst)
{
	com_init(com);
	// parse_redir(lst, com);
	if (get_cmd_path(lst, com) == -1)
		return (-1);
	com->cmd_args = get_cmd_args(lst);
	ft_arriter_str(com->cmd_args, prout);
	return (1);
}
