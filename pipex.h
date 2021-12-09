/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:02:26 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/08 20:26:09 by vguttenb         ###   ########.fr       */
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
# include "libft/libft.h"

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
	char	**envp;
}				t_envir;

char		**get_paths(char **envp);
char		*search_comm(char *comm, char **paths);
void		exec(t_execord *execorder, int rfd, int wfd, char **envp);
void		take_output(int rfd, char *xfile);
int			get_closed_fd(void);
int			big_exec(t_envir *env, int rfd, int ind);
void		exec_comm(t_envir *env, int ind, int rfd, int wfd);

# endif