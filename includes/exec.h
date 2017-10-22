/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:06:02 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/22 19:22:19 by nmougino         ###   ########.fr       */
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
	char		*heredoc;
	int			hdfd[2];
	int			i;
}				t_com;

typedef struct	s_pre_exec
{
	t_com		com;
	int			save[3];
	char		**env;
}				t_pre_exec;

# define CMD_SUCCESS 0
# define CMD_FAIL 1

/*
** apply_op.c
*/

int				apply_op(t_btree *r);

/*
** apply_pipe_left.c
*/

int				pipe_left(t_btree *r, int *fd, char *hd);

/*
** apply_pipe.c
*/

void			prout(int rip, t_pre_exec *pre, t_btree *nr,
					int *fd) __attribute__((noreturn));
int				ft_pipe_to_right(int *fd, t_btree *node_right);
int				ft_launch_pipeline(t_btree *node_left, t_btree *node_right);
int				apply_pipe(t_btree *r);

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

int				parse_redir(t_list *cmdl, t_com *com);

/*
** create_simple.c
*/

void			create_simple(t_com *com, t_list *lst);

/*
** exec_ast.c
*/

int				exec_ast(t_btree *r);

/*
** exec_simple.c
*/

void			exec_simple(int i, t_com *com,
					char **env) __attribute__((noreturn));

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
** pre_close_exec.c
*/

void			prepare_exec(t_pre_exec *pre, t_btree *tar);
void			close_exec(t_pre_exec *pre);

/*
** ERNNO ERROR MESSAGES FOR EXECVE
*/

# define EXEC_E2BIG_1 "The number of bytes in the new process's argument list i"
# define EXEC_E2BIG_2 "s larger than the system-imposed limit. This limit is sp"
# define EXEC_E2BIG_3 "ecified by the sysctl(3) MIB variable KERN_ARGMAX."
# define EXEC_E2BIG EXEC_E2BIG_1 EXEC_E2BIG_2 EXEC_E2BIG_3
# define EXEC_EACCES_1 "Search permission is denied for a component of the path"
# define EXEC_EACCES_2 " prefix. OR The new process file is not an ordinary fil"
# define EXEC_EACCES_3 "e. OR The new process file mode denies execute permissi"
# define EXEC_EACCES_4 "on. OR The new process file is on a filesystem mounted "
# define EXEC_EACCES_5 "with execution disabled (MNT_NOEXEC in <sys/mount.h>)."
# define EXEC_EACCES_6  EXEC_EACCES_1 EXEC_EACCES_2 EXEC_EACCES_3 EXEC_EACCES_4
# define EXEC_EACCES EXEC_EACCES_6 EXEC_EACCES_5
# define EXEC_EFAULT_1 "The new process file is not as long as indicated by the"
# define EXEC_EFAULT_2 " size values in its header. OR Path, argv, or envp poin"
# define EXEC_EFAULT_3 "t to an illegal address."
# define EXEC_EFAULT EXEC_EFAULT_1 EXEC_EFAULT_2 EXEC_EFAULT_3
# define EXEC_EIO "An I/O error occurred while reading from the file system."
# define EXEC_ELOOP_1 "Too many symbolic links were encountered in translating "
# define EXEC_ELOOP_2 "the pathname.  This is taken to be indicative of a loopi"
# define EXEC_ELOOP EXEC_ELOOP_1 EXEC_ELOOP_2 "ng symbolic link."
# define EXEC_ENAMETL_1 "A component of a pathname exceeded {NAME_MAX} cha"
# define EXEC_ENAMETL_2 "racters, or an entire path name exceeded {PATH_MA"
# define EXEC_ENAMETOOLONG EXEC_ENAMETL_1 EXEC_ENAMETL_2 "X} characters."
# define EXEC_ENOENT "The new process file does not exist."
# define EXEC_ENOEXEC_1 "The new process file has the appropriate access permis"
# define EXEC_ENOEXEC_2 "sion, but has an unrecognized format (e.g., an invalid"
# define EXEC_ENOEXEC_3 " magic number in its header)."
# define EXEC_ENOEXEC EXEC_ENOEXEC_1 EXEC_ENOEXEC_2 EXEC_ENOEXEC_3
# define EXEC_ENOMEM_1 "The new process requires more virtual memory than is al"
# define EXEC_ENOMEM EXEC_ENOMEM_1"lowed by the imposed maximum (getrlimit(2))."
# define EXEC_ENOTDIR "A component of the path prefix is not a directory."
# define EXEC_ETXTBSY_1 "The new process file is a pure procedure (shared text)"
# define EXEC_ETXTBSY_2 " file that is currently open for writing or reading by"
# define EXEC_ETXTBSY EXEC_ETXTBSY_1 EXEC_ETXTBSY_2 " some process."

#endif
