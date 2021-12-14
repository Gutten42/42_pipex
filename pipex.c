/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:50:55 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/14 14:07:25 by vguttenb         ###   ########.fr       */
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
	result = (char **)malloc(sizeof(char *) * 2);
	result[0] = (char *)malloc(sizeof(char));
	result[0][1] = '\0';
	result[1] = NULL;
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	t_envir		env;
	int			rfd;
	int			ind;

	env.tty_mode = 0;
	if (argc > 1 && (ft_strnstr(argv[1], "here_doc", 8) && argv[1][8] == '\0'))
		env.tty_mode = 1;
	if (argc < 3 || (env.tty_mode && argc < 4))
	{
		ft_putstr_fd("Error: not enough arguments, ", 1);
		if (env.tty_mode)
			ft_putstr_fd("try: ./pipex here_doc LIMITER (cmds) file\n", 1);
		else
			ft_putstr_fd("try: ./pipex file1 (cmds) file2\n", 1);
		exit(0);
	}
	env.paths = get_paths(envp);
	env.argv = argv;
	env.argc = argc - 1;
	env.envp = envp;
	env.sp_flag = O_TRUNC;
	ind = 2;
	rfd = get_rfd(&env, &ind);
	piping(&env, ind, rfd);
	free_paths(env.paths);
}
