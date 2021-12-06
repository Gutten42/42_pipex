
#include "pipex.h"

int	exec(t_envir *env, int rfd, int wfd, int ind)
{
	t_execord	*exec;
	pid_t		pidC;
	
	exec = get_execord(env->argv[ind], env->paths);
	pidC = fork();
	if (pidC == 0)
	{
		dup2(rfd, STDIN_FILENO);
		close(rfd);
		dup2(wfd, STDOUT_FILENO);
		close(wfd);
		execve(exec->comm, exec->argsum, env->envp);
		perror(exec->argsum[0]);
		ind = 0;
	}
	else
	{
		close(rfd);
		close(wfd);
		free(exec);
	}
	if (!ind)
		return(0);
	return(1);
}
