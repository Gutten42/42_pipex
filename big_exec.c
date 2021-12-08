/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:13:12 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/07 18:22:35 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	big_exec(t_envir *env, int rfd)
{
	int	ind;
	int	p_ind;
	
	ind = 2;
	p_ind = 2;
	if (rfd < 0)
	{
		rfd = get_closed_fd();
		ind++;
		if (!env->argv[ind + 2])
			return (-1);
	}
	pipe(fd[0]);
	p_ind += exec(env, rfd, fd[0][1], ind);
	while (env->argv[ind + 2])
	{
		ind++;
		pipe(fd[p_ind % 2]);
		p_ind += exec(&env, fd[(p_ind + 1) % 2][0], fd[p_ind % 2][1], ind);
	}
	return (fd[p_ind % 2][0]);
	// output(fd[p_ind % 2][0], argv[p_ind + 1]);
}