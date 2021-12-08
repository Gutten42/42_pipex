/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:04:02 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/08 20:38:13 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	nullfd(void)
{
	int	fd[2];

	pipe(fd);
	close(fd[1]);
	return(fd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_envir		env;
	int			ind;
	int			rfd;
	
	env.paths = get_paths(envp);
	env.argv = argv;
	env.envp = envp;
	if (argc < 3)
		exit(0);
	ind = 2;
	rfd = open(argv[1], O_RDONLY);
	if (rfd < 0)
	{
		printf("%s: %s\n", strerror(errno), argv[1]);
		ind++;
		rfd = nullfd();
	}
	if (argv[ind + 1])
		rfd = big_exec(&env, rfd, ind, envp);
	take_output(rfd, argv[argc - 1]);
	system("leaks pipex");
	printf("Success\n");
}
