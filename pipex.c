/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:50:55 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/10 19:01:42 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_paths(char **paths)
{
	int	ind;

	ind = 0;
	while (paths[ind])
		free(paths[ind++]);
	free(paths);
}

static char	**get_paths(char **envp)
{
	int		i;
	char	*paths;
	char	**result;

	i = 0;
	while (envp[i])
	{
		paths = ft_strnstr(envp[i], "PATH=", 5);
		if (paths)
			return (ft_split(paths + sizeof(char) * 5, ':'));
		i++;
	}
	result = (char**)malloc(sizeof(char*) * 2);
	result[0] = (char*)malloc(sizeof(char));
	result[0][1] = '\0';
	result[1] = NULL;
	return (result);
}

int	get_tty(char *limiter)
{
	int		pip[2];
	char	buffer[2];
	char	*keeper;

	pipe(pip);
	buffer[1] = '\0';
	while (1)
	{
		keeper = "";
		write(1, "> ", 2);
		while (!ft_strchr(keeper, '\n'))
		{
			read(0, &buffer[0], 1);
			keeper = ft_strjoin(keeper, buffer);
		}
		if (ft_strnstr(keeper, limiter, ft_strlen(limiter))) //RECUERDA QUE HAS CAMBIADO STRCHR
			break ;
		write(pip[WR_END], keeper, ft_strlen(keeper));
	}
	close(pip[WR_END]);
	return (pip[RD_END]);
}

int	main(int argc, char **argv, char **envp)
{
	t_envir		env;
	int			rfd;
	
	//printf("%d\n", O_APPEND);
	if (argc < 3)
	{
		ft_putstr_fd("Error: not enough arguments, pipex needs at least an input file and an output file\n", 1);
		exit(0);
	}
	env.paths = get_paths(envp);
	env.argv = argv;
	env.argc = argc - 1;
	env.envp = envp;
	env.sp_flag = 1;
	if (ft_strnstr(argv[1], "here_doc", 8) && argv[1][8] == '\0')
	{
		env.sp_flag = 2;
		rfd = get_tty(argv[2]);
	}
	piping(&env, 3, rfd);
	free_paths(env.paths);
	//system("leaks pipex");
	printf("Success\n");
}
