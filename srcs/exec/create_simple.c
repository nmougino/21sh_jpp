/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 18:15:19 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/24 18:59:48 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		com_init(t_com *com)
{
	com->com_name = NULL;
	com->cmd_path = NULL;
	com->cmd_args = NULL;
	com->fd[0] = 0;
	com->fd[1] = 1;
	com->fd[2] = 2;
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

static char		**create_args_tab(char *com_name, t_list *lst, size_t len)
{
	char	**ans;

	ans = malloc(sizeof(char*) * (len + 2));
	ans[0] = ft_strdup(com_name);
	ans[len + 1] = NULL;
	if (len)
	{
		len = 1;
		while (lst)
		{
			if ((((t_token*)(lst->content))->type) == WORD)
				ans[len++] = ft_strdup(((t_token*)(lst->content))->content);
			else if ((((t_token*)(lst->content))->type) > IO_NUMBER)
				lst = lst->next;
			lst = lst->next;
		}
	}
	return (ans);
}

static char		**get_cmd_args(t_com *com, t_list *lst)
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
	return (create_args_tab(com->com_name, lst, len));
}

int				create_simple(t_com *com, t_list *lst)
{
	int	i;

	com_init(com);
	parse_redir(lst, com);
	if ((i = get_cmd_path(lst, com)) != 1)
		return (i);
	com->cmd_args = get_cmd_args(com, lst);
	return (1);
}
