/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 17:16:09 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/12 21:22:51 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	do_it_han_red(char *tok, int io, t_com *com, char *next)
{
	int	tmp;

	if (!ft_strcmp(tok, LESS)) // "<"
	{
		if ((tmp = ft_open(next, O_CREAT | O_RDONLY, "sh")) == -1)
			return (-1);
		com->fd[io == -1 ? 0 : io] = tmp;
	}
	else if (!ft_strcmp(tok, GREAT)) // ">"
	{
		if ((tmp = ft_open(next, O_CREAT | O_WRONLY | O_TRUNC, "sh")) == -1)
			return (-1);
		com->fd[io == -1 ? 1 : io] = tmp;
	}
	else if (!ft_strcmp(tok, DGREAT)) // ">>"
	{
		if ((tmp = ft_open(next, O_CREAT | O_WRONLY, "sh")) == -1)
			return (-1);
		com->fd[io == -1 ? 1 : io] = tmp;
	}
	else if (!ft_strcmp(tok, LESSAND)) // "<&"
		com->fd[io == -1 ? 1 : -1] = ft_atoi(next);
	else if (!ft_strcmp(tok, GREATAND)) // ">&"
		com->fd[io == -1 ? 0 : -1] = ft_atoi(next);
	return (0);
}

static int	handle_redir(t_list *cmdl, t_com *com)
{
	int	tmp;
	int	i;

	tmp = -1;
	while (cmdl)
	{
		i = 0;
		if (((t_token*)(cmdl->content))->type == IO_NUMBER)
			tmp = ft_atoi(((t_token*)(cmdl->content))->content);
		else if ((((t_token*)(cmdl->content))->type == OP_REDIRECT) &&
			!ft_strcmp(((t_token*)(cmdl->next->content))->content, "-"))
			com->to_close[tmp == -1 ? 1 : tmp] = 1;
		else if (((t_token*)(cmdl->content))->type == OP_REDIRECT)
		{
			i = do_it_han_red(((t_token*)(cmdl->content))->content, tmp, com,
			(((t_token*)(cmdl->next->content))->content));
			tmp = -1;
		}
		if (i == -1)
			return (-1);
		cmdl = cmdl->next;
	}
	return (0);
}

/* In order to exec the cmdl,
	we need to know :
		1: the cmd's path
		2: the args
		3: the environment
	Before that we have to :
	handle the redirections
*/

/*
** This function WILL NOT fork in order to create a new process.
*/

void		exec_simple(t_list *lst)
{
	t_com	com;

	handle_redir(lst, &com);
	if (com.to_close[0])
		close(0);
	if (com.to_close[1])
		close(1);
	if (com.to_close[2])
		close(2);
}
