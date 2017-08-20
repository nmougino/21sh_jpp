/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:06:02 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/20 18:15:21 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "shell.h"

# include <sys/stat.h>

typedef struct	s_com
{
	char		*com_name;
	char		*cmd_path;
	char		**cmd_args;
	int			fd[3];
	int			to_close[3];
}				t_com;

/*
** parse_redir.c
*/

void			parse_redir(t_list *cmdl, t_com *com);

/*
** create_simple.c
*/

int				create_simple(t_com *com, t_list *lst);

/*
** exec_simple.c
*/

int				exec_simple(t_list *lst);

/*
** get_cmd_path.c
*/

int				get_cmd_path(t_list *lst, t_com *com);

/*
** handle_redir.c
*/

void			handle_redir(t_com *com);

#endif
