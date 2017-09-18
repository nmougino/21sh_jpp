/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:06:02 by nmougino          #+#    #+#             */
/*   Updated: 2017/09/18 11:12:52 by nmougino         ###   ########.fr       */
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
	char		*heredoc; // contient d'abord le delimiteur, puis la chaine, == NULL alors pas de heredoc
	int			hdfd[2]; // pipe pour l'ecriture des heredoc
}				t_com;

# define CMD_SUCCESS 0
# define CMD_FAIL 1

/*
** apply_op.c
*/

int				apply_op(t_btree *r);

/*
** apply_pipe.c
*/

int				apply_pipe(t_btree *r, int *pfd);

/*
** clodup.c
*/

void			clodup(int *fd, int i);

/*
** com_del.c
*/

void			com_del(t_com *com);

/*
** parse_redir.c
*/

void			parse_redir(t_list *cmdl, t_com *com);

/*
** create_simple.c
*/

int				create_simple(t_com *com, t_list *lst);

/*
** exec_ast.c
*/

int				exec_ast(t_btree *r);

/*
** exec_simple.c
*/

void			exec_simple(int i, t_com *com, char **env)
					__attribute__ ((noreturn));

/*
** get_cmd_path.c
*/

int				get_cmd_path(t_list *lst, t_com *com);

/*
** handle_redir.c
*/

void			restore_redir(int *save);
void			handle_redir(t_com *com, int *save);

/*
** ERNNO ERROR MESSAGES FOR EXECVE
*/

# define EXEC_E2BIG "The number of bytes in the new process's argument list i\
s larger than the system-imposed limit. This limit is specified by t\
he sysctl(3) MIB variable KERN_ARGMAX."
# define EXEC_EACCES "Search permission is denied for a component of the p\
ath prefix. OR The new process file is not an ordinary file. OR The ne\
w process file mode denies execute permission. OR The new process fi\
le is on a filesystem mounted with execution disabled (MNT_NOE\
XEC in <sys/mount.h>)."
# define EXEC_EFAULT "The new process file is not as long as indicated by th\
e size values in its header. OR Path, argv, or envp point to an il\
legal address."
# define EXEC_EIO "An I/O error occurred while reading from the file system."
# define EXEC_ELOOP "Too many symbolic links were encountered in translating t\
he pathname.  This is taken to be indicative of a looping symbolic l\
ink."
# define EXEC_ENAMETOOLONG "A component of a pathname exceeded {NAME_MAX} char\
acters, or an entire path name exceeded {PATH_MAX} characters."
# define EXEC_ENOENT "The new process file does not exist."
# define EXEC_ENOEXEC "The new process file has the appropriate access permiss\
ion, but has an unrecognized format (e.g., an invalid magic number i\
n its header)."
# define EXEC_ENOMEM "The new process requires more virtual memory than is al\
lowed by the imposed maximum (getrlimit(2))."
# define EXEC_ENOTDIR "A component of the path prefix is not a directory."
# define EXEC_ETXTBSY "The new process file is a pure procedure (shared text\
) file that is currently open for writing or reading by some process."

#endif
