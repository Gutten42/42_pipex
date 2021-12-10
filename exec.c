
#include "pipex.h"

void	exec(t_execord *execorder, int rfd, int *wfd, char **envp)
{
	pid_t		pidC;

	pidC = fork();
	if (pidC == 0)
	{
		close(wfd[0]);
		dup2(rfd, STDIN_FILENO);
		close(rfd);
		dup2(wfd[1], STDOUT_FILENO);
		close(wfd[1]);
		execve(execorder->comm, execorder->argsum, envp);
		perror(execorder->argsum[0]);
	}
}
