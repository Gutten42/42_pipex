/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:02:26 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/04 17:35:36 by vguttenb         ###   ########.fr       */
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
}				t_execord;

typedef struct s_envir
{
	char	**paths;
	char	**argv;
	char	**envp;
}				t_envir;

char		**get_paths(char **envp);
char		*search_comm(char *comm, char **paths);
t_execord	*get_execord(char *command, char **paths);
int			exec(t_envir *env, int rfd, int wfd, int ind);
void		output(int rfd, char *xfile);

# endif