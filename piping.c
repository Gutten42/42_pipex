/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:24:40 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/13 19:06:51 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	take_output(int wfd, int rfd)
{
	char	result;
	ssize_t more;
	
	more = read(rfd, &result, 1);
	while (more > 0)
	{
		write(wfd, &result, 1);
		more = read(rfd, &result, 1);
	}
	close(wfd);	
}

void	piping(t_envir *env, int ind, int rfd)
{
	int	wfd;
	
	if (ind < env->argc || ind == 2 || env->tty_mode)
	{
		wfd = open(env->argv[env->argc],
				O_CREAT | O_WRONLY | env->sp_flag, 0666);
		if (wfd < 0)
		{
			err_msg(strerror(errno), env->argv[env->argc]);
			env->argc -= 1;
		}
		if (ind < env->argc)
			rfd = exec_manage(env, rfd, ind);
		if (wfd > 0)
			take_output(wfd, rfd);
	}
	close(rfd);
}