/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 18:20:07 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/10 00:24:13 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	redir_put_error(char *tar)
{
	struct stat	buf;
	if (lstat(tar, &buf))
		return (ft_dprintf(2, "sh: no such file or directory: %s\n", tar) && 0);
	else if (access(tar, F_OK))
		ft_dprintf(2, "sh: file is not accessible: %s\n", tar);
	else if (access(tar, X_OK))
		ft_dprintf(2, "sh: permission denied: %s\n", tar);
	else
		ft_dprintf(2, "sh: unknow error: %s\n", tar);
	return (0);
}

static int	do_it_han_red(char *tok, int io, t_com *com, char *next)
{
	int	tmp;
	int	flag;
	int	dest;

	if (!ft_strcmp(tok, DLESS))
		com->heredoc = next;
	else if (!ft_strcmp(tok, LESSAND))
		com->fd[io == -1 ? 1 : io] = ft_atoi(next);
	else if (!ft_strcmp(tok, GREATAND))
		com->fd[io == -1 ? 0 : io] = ft_atoi(next);
	else
	{
		dest = (!ft_strcmp(tok, GREAT) || !ft_strcmp(tok, DGREAT)) ? 1 : 0;
		flag = (!ft_strcmp(tok, LESS)) ? O_RDONLY : O_CREAT | O_WRONLY;
		flag = (!ft_strcmp(tok, GREAT)) ? flag | O_TRUNC : flag;
		if ((tmp = open(next, flag, 0644)) == -1)
			return (redir_put_error(next));
		com->fd[io == -1 ? dest : io] = tmp;
	}
	return (1);
}

int			parse_redir(t_list *cmdl, t_com *com)
{
	int	tmp;

	tmp = -1;
	while (cmdl)
	{
		if (((t_token*)(cmdl->content))->type == IO_NUMBER)
			tmp = ft_atoi(((t_token*)(cmdl->content))->content);
		else if ((((t_token*)(cmdl->content))->type == OP_REDIRECT) &&
			!ft_strcmp(((t_token*)(cmdl->next->content))->content, "-"))
			com->to_close[tmp == -1 ? 1 : tmp] = 1;
		else if (((t_token*)(cmdl->content))->type == OP_REDIRECT)
		{
			if (!do_it_han_red(((t_token*)(cmdl->content))->content, tmp, com,
			(((t_token*)(cmdl->next->content))->content)))
				return (0);
			tmp = -1;
		}
		cmdl = cmdl->next;
	}
	return (1);
}
