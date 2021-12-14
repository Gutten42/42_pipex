/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:02:26 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/14 13:08:27 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define RD_END	0
# define WR_END	1

typedef struct s_execord
{
	char	*comm;
	char	**argsum;
	char	free;
}				t_execord;

typedef struct s_envir
{
	char	**paths;
	char	**argv;
	int		argc;
	char	**envp;
	int		sp_flag;
	char	tty_mode;	
}				t_envir;

void		piping(t_envir *env, int ind, int rfd);
char		*search_comm(char *comm, char **paths);
int			exec_manage(t_envir *env, int rfd, int ind);
void		exec(t_execord *execorder, int rfd, int *wfd, char **envp);
int			get_rfd(t_envir *env, int *ind);
void		err_msg(char *err, char *filename);
char		*sec_strchr(const char *str, int srch);
char		*gnl_strjoin(char *keeper, char *buffer);

#endif