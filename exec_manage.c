/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:49:21 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/10 18:49:21 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execfree(t_execord *exec_order)
{
	int	ind;
	
	if (exec_order->free && exec_order->comm)
		free(exec_order->comm);
	ind = 0;
	while (exec_order->argsum[ind])
	{
		free(exec_order->argsum[ind]);
		ind++;	
	}
	free(exec_order->argsum);
}

static void	get_execord(char *command, char **paths, t_execord *result)
{
	char		**complus;
	char		*last_bar;
	
	complus = ft_split(command, ' ');
	last_bar = ft_strrchr(complus[0], '/');
	if (last_bar)
	{
		result->comm = command;
		if (access(result->comm, F_OK) < 0)
		 	result->comm = NULL;
		result->argsum = complus;
		last_bar = ft_strdup(last_bar + sizeof(char));
		free(complus[0]);
		result->argsum[0] = last_bar;
		result->free = 0;
	}
	else
	{
		result->comm = search_comm(complus[0], paths);
		result->argsum = complus;
		result->free = 1;
	}
}

void	exec_comm(t_envir *env, int ind, int rfd, int *wfd)
{
	t_execord	exec_order;

	if (!env->argv[ind] || !env->argv[ind][0])
		ft_putstr_fd("pipex: empty argument\n", 1);
	else
	{
		get_execord(env->argv[ind], env->paths, &exec_order);
		if (!exec_order.comm)
		{
			if (exec_order.free)
				ft_putstr_fd("pipex: command not found\n", 1);
			else
				ft_putstr_fd("pipex: file not found\n", 1);
		}
		else
			exec(&exec_order, rfd, wfd, env->envp);
		execfree(&exec_order);
	}
	close(rfd);
	close(wfd[WR_END]);
}

/*int	big_exec(t_envir *env, int rfd, int ind)
{
	int	fd[2][2];

	pipe(fd[ind % 2]);
	if (!pipe(fd[ind % 2]))
	{
		close(fd[ind % 2][0]);
		close(fd[ind % 2][1]);
		return(rfd);
	}
	exec_comm(env, ind, rfd, fd[ind % 2]);
	while (env->argv[ind + 2])
	{
		ind++;
		pipe(fd[ind % 2]);
		if (!pipe(fd[ind % 2]))
		{
			close(fd[ind % 2][0]);
			close(fd[ind % 2][1]);
			ind--;
			break ;
		}
		exec_comm(env, ind,  fd[(ind + 1) % 2][0], fd[ind % 2]);
	}
	return(fd[ind % 2][0]);
}*/

int	exec_manage(t_envir *env, int rfd, int ind)
{
	int	fd[2][2];

	while (ind < env->argc)
	{
		if (pipe(fd[ind % 2]) < 0)
		{
			close(fd[ind % 2][RD_END]);
			close(fd[ind % 2][WR_END]);
			return (rfd);
		}
		exec_comm(env, ind, rfd, fd[ind % 2]);
		rfd = fd[ind % 2][RD_END];
		ind++;
	}
	return(rfd);
}