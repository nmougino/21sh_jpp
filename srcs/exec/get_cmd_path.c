/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:01:19 by nmougino          #+#    #+#             */
/*   Updated: 2017/08/18 16:54:52 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*find_com_name(t_list *lst)
{
	while (lst)
	{
		if (((t_token*)(lst->content))->type == WORD)
			return (((t_token*)(lst->content))->content);
		else if (((t_token*)(lst->content))->type > IO_NUMBER)
			lst = lst->next->next;
		else
			lst = lst->next;
	}
	return (NULL);
}

static size_t	path_cpy(char *path, char *com_name, char **ans)
{
	size_t	len;

	len = 0;
	while (path[len] && path[len] != ':')
		++len;
	*ans = ft_strnew(len + 1 + ft_strlen(com_name));
	ft_strncat(*ans, path, len);
	(*ans)[len] = '/';
	ft_strcat(*ans + len + 1, com_name);
	if (path[len])
		++len;
	return (len);
}

static char	 	*find_com_path(char *path, char *com_name)
{
	char		*ans;
	size_t		len;
	struct stat	buf;

	ans = NULL;
	len = path_cpy(path, com_name, &ans);
	while (*path && lstat(ans, &buf))
	{
		ft_strdel(&ans);
		path += len;
		len = path_cpy(path, com_name, &ans);
	}
	if (ans && lstat(ans, &buf))
		ft_strdel(&ans);
	return (ans);
}

static int		find_file(char *com_name, t_com *com)
{
	struct stat	buf;

	if (lstat(com_name, &buf))
		return (ft_dprintf(2, "sh: no such file or directory: %s\n", com_name));
	else
		com->cmd_path = ft_strdup(com_name);
	return (0);
}

/*
** Renvoie 0 dans le cas ou aucune commande n'a ete detectee dans la ligne
** Renvoie -1 et affiche l'erreur correspondante dans le cas ou le fichier
** est introuvable.
**
** retour	| com_path	| interpretation
**   -1		| NULL		| commande introuvable
**   -1		| NULL		| fichier introuvable
**   0		| NULL		| aucune commande specifiee
**   1		| !NULL		| commande localisee et retournee
**
*/

int				get_cmd_path(t_list *lst, t_com *com)
{
	char	*path;
	char	*com_name;

	if (!(com_name = find_com_name(lst)))
		return (0);
	if (ft_strchr(com_name, '/'))
		return (find_file(com_name, com) ? -1 : 1);
	else if ((path = get_env("PATH")))
		com->cmd_path = find_com_path(path, com_name);
	if (!com->cmd_path)
		return ((ft_dprintf(2, "sh: commande not found: %s\n", com_name) && 0)
			- 1);
	return (1);
}
