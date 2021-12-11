/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:24:40 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/10 19:15:59 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	take_output(int *fd, int rfd)
{
	char	result;
	ssize_t more;
	
	more = read(rfd, &result, 1);
	while (more > 0)
	{
		write(fd[WR_END], &result, 1);
		more = read(rfd, &result, 1);
	}
	close(fd[WR_END]);	
}

/*static int	nullfd(void)
{
	int	fd[2];

	pipe(fd);
	close(fd[WR_END]);
	return(fd[RD_END]);
}*/

static void	err_msg(char *err, char *filename)
{
	ft_putstr_fd("pipex: ", 1);
	ft_putstr_fd(err, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(filename, 1);
	ft_putstr_fd("\n", 1);
}

void	piping(t_envir *env, int ind, int rfd)
{
	int	fd[2];
	
	/*fd[RD_END] = open(env->argv[1], O_RDONLY);
	if (fd[RD_END] < 0)
	{
		err_msg(strerror(errno), env->argv[1]);
		ind++;
		fd[RD_END] = nullfd();
	}*/
	if (ind < env->argc || ind == 2) // Esto habrá que revisarlo cuando añadamos el bonus
	{
		fd[WR_END] = open(env->argv[env->argc],
				O_CREAT | O_WRONLY | O_TRUNC * env->sp_flag, 0666);
		if (fd[WR_END] < 0)
		{
			err_msg(strerror(errno), env->argv[env->argc]);
			env->argc -= 1;
		}
		if (ind < env->argc)
			rfd = exec_manage(env, rfd/*fd[RD_END]*/, ind);
		if (fd[WR_END] > 0)
			take_output(fd, rfd);
	}
	close(fd[RD_END]);
}