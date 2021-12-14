/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:47:39 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/14 13:06:10 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	nullfd(void)
{
	int	fd[2];

	pipe(fd);
	close(fd[WR_END]);
	return (fd[RD_END]);
}

static int	get_tty(char *limiter)
{
	int		pip[2];
	char	buffer[2];
	char	*keeper;

	pipe(pip);
	buffer[1] = '\0';
	while (1)
	{
		keeper = NULL;
		write(1, "heredoc> ", 9);
		while (!sec_strchr(keeper, '\n'))
		{
			read(0, &buffer[0], 1);
			keeper = gnl_strjoin(keeper, buffer);
		}
		if (ft_strnstr(keeper, limiter, ft_strlen(limiter))
			&& keeper[ft_strlen(limiter)] == '\n')
			break ;
		write(pip[WR_END], keeper, ft_strlen(keeper));
		free (keeper);
	}
	free (keeper);
	close(pip[WR_END]);
	return (pip[RD_END]);
}

int	get_rfd(t_envir *env, int *ind)
{
	int	rfd;

	if (env->tty_mode)
	{
		rfd = get_tty(env->argv[2]);
		env->sp_flag = O_APPEND;
		*ind = 3;
	}
	else
	{
		rfd = open(env->argv[1], O_RDONLY);
		if (rfd < 0)
		{
			err_msg(strerror(errno), env->argv[1]);
			rfd = nullfd();
			*ind = 3;
		}
	}
	return (rfd);
}
