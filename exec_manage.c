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

static void	get_execord(char *command, char **paths, t_execord *exec_order)
{
	char		**complus;
	char		*last_bar;
	
	complus = ft_split(command, ' ');
	last_bar = ft_strrchr(complus[0], '/');
	if (last_bar)
	{
		exec_order->comm = command;
		if (access(exec_order->comm, F_OK) < 0)
		 	exec_order->comm = NULL;
		exec_order->argsum = complus;
		last_bar = ft_strdup(last_bar + sizeof(char));
		free(complus[0]);
		exec_order->argsum[0] = last_bar;
		exec_order->free = 0;
	}
	else
	{
		exec_order->comm = search_comm(complus[0], paths);
		exec_order->argsum = complus;
		exec_order->free = 1;
	}
}

static void	exec_comm(t_envir *env, int ind, int rfd, int *pip)
{
	t_execord	exec_order;

	if (!env->argv[ind] || !env->argv[ind][0])
		ft_putstr_fd("pipex: empty argument\n", 1);
	else
	{
		get_execord(env->argv[ind], env->paths, &exec_order);
		if (!exec_order.comm)
		{
			ft_putstr_fd("pipex: ", 1);
			ft_putstr_fd(exec_order.argsum[0], 1);
			if (exec_order.free)
				ft_putstr_fd(": command not found\n", 1);
			else
				ft_putstr_fd(": file not found\n", 1);
		}
		else
			exec(&exec_order, rfd, pip, env->envp);
		execfree(&exec_order);
	}
	close(rfd);
	close(pip[WR_END]);
}

int	exec_manage(t_envir *env, int rfd, int ind)
{
	int	pip[2][2];

	while (ind < env->argc)
	{
		if (pipe(pip[ind % 2]) < 0)
		{
			close(pip[ind % 2][RD_END]);
			close(pip[ind % 2][WR_END]);
			return (rfd);
		}
		exec_comm(env, ind, rfd, pip[ind % 2]);
		rfd = pip[ind % 2][RD_END];
		ind++;
	}
	return(rfd);
}