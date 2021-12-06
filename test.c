/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:04:02 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/04 20:36:33 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_envir		env;
	int			fd[2][2];
	int			ind;
	int			rfd;
	
	env.paths = get_paths(envp);
	env.argv = argv;
	env.envp = envp;
	if (argc < 3)
		exit(0);
	rfd = open(argv[1], O_RDONLY);
	if (rfd < 0)
		printf("%s: %s\n", strerror(errno), argv[1]);
	else if (argc > 3)
	{
		ind = 2;
		pipe(fd[0]);
		exec(&env, rfd, fd[0][1], ind);
		while (ind < (argc - 2))
		{
			ind++;
			pipe(fd[ind % 2]);
			exec(&env, fd[(ind + 1) % 2][0], fd[ind % 2][1], ind);
		}
		output(fd[ind % 2][0], argv[ind + 1]);
	}
	else
		output(rfd, argv[2]);
	printf("Success\n");	
}
