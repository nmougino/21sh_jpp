/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_to_canonical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 14:34:19 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/24 19:52:56 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	to_can_checkpath(char **arr)
{
	int			ans;
	struct stat	buf;
	char		**tmp;
	char		*str;

	tmp = ft_arrstrncpy(arr, ft_arrlen(arr, sizeof(char *)) - 1);
	str = *arr ? ft_arrglu(arr, "/", 1) : ft_strdup("/");
	ft_strinschar(&str, 0, '/');
	if (lstat(str, &buf) || !S_ISDIR(buf.st_mode))
		ans = ft_dprintf(2, "cd: %s: not a directory\n", str) && 0;
	else
		ans = 1;
	ft_strdel(&str);
	ft_arrdel((void***)&arr);
	ft_arrdel((void***)&tmp);
	return (ans);
}

static int	to_can_loop(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strequ(arr[i], "."))
			ft_arr_move_left_str(arr + i);
		else if (i && ft_strequ(arr[i], "..") && !ft_strequ(arr[i - 1], ".."))
		{
			if (!to_can_checkpath(ft_arrstrncpy(arr, (size_t)i - 1)))
				return (0);
			ft_arr_move_left_str(arr + i - 1);
			ft_arr_move_left_str(arr + i - 1);
			--i;
		}
		else
			++i;
	}
	return (1);
}

int			bi_cd_to_canonical(char **str)
{
	char	**arr;
	char	*tmp;

	if ((*str)[0] != '/')
		return (1);
	arr = ft_strsplit(*str, '/');
	if (!to_can_loop(arr))
	{
		ft_strdel(str);
		ft_arrdel((void***)&arr);
		return (0);
	}
	tmp = *arr ? ft_arrglu(arr, "/", 1) : ft_strdup("");
	ft_strinschar(&tmp, 0, '/');
	ft_arrdel((void***)&arr);
	ft_strdel(str);
	*str = tmp;
	return (1);
}
