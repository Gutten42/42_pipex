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

typedef struct s_execord
{
	char	*comm;
	char	**argsum;
}				t_execord;

int	exec(t_execord *execord, int rfd, int wfd, char **envp)
{
	pid_t	pidC;
	
	pidC = fork();
	if (pidC == 0)
	{
		dup2(rfd, STDIN_FILENO);
		close(rfd);
		dup2(wfd, STDOUT_FILENO);
		close(wfd);
		execve(execord->comm, execord->argsum, envp);
	}
	else
	{
		close(rfd);
		close(wfd);
		free(execord);
		return (1);
	}
	return	(0);
}

t_execord	*get_execord(char *command, char **paths)
{
	t_execord	*result;
	char		**complus;
	char		*last_bar;
	
	complus = ft_split(command, ' ');
	result = (t_execord *)malloc(sizeof(t_execord));
	last_bar = ft_strrchr(complus[0], '/');
	if (last_bar)
	{
		result->comm = command;
		result->argsum = complus;
		result->argsum[0] = ft_strdup(last_bar + sizeof(char));
		free(complus[0]);
	}
	else
	{
		result->comm = search_comm(complus[0], paths);
		result->argsum = complus;
	}
	return (result);
}

void	output(int rfd, char *xfile)
{
	int		wfd;
	char	result;
	ssize_t more;
	
	wfd = open(xfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (wfd < 0)
		printf("%s: %s\n", strerror(errno), xfile);
	else
	{
		more = read(rfd, &result, 1);
		while (more > 0)
		{
			//write(1, &result, 1);
			write(wfd, &result, 1);
			more = read(rfd, &result, 1);
		}
		close(wfd);	
	}
	close(rfd);
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	int		fd[2][2];
	int		ind;
	t_execord	*pepe;
	int		rfd;
	
	paths = get_paths(envp);
	rfd = open(argv[1], O_RDONLY);
	if (rfd < 0)
		printf("%s: %s\n", strerror(errno), argv[1]);
	else
	{
		pepe = get_execord(argv[2], paths);
		pipe(fd[0]);
		exec(pepe, rfd, fd[0][1], envp);
		ind = 3;
		while (ind < (argc - 1))
		{
			pepe = get_execord(argv[ind], paths);
			pipe(fd[ind % 2]);
			exec(pepe, fd[(ind + 1) % 2][0], fd[ind % 2][1], envp);
			ind++;
		}
		output(fd[(ind + 1) % 2][0], argv[ind]);
	}
	printf("Success\n");	
}
