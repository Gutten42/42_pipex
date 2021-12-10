
#include "pipex.h"

void	exec(t_execord *execorder, int rfd, int *wfd, char **envp)
{
	pid_t		pidC;

	pidC = fork();
	if (pidC == -1)
		perror("fork");
	else if (pidC == 0)
	{
		close(wfd[RD_END]);
		dup2(rfd, STDIN_FILENO);
		close(rfd);
		dup2(wfd[WR_END], STDOUT_FILENO);
		close(wfd[WR_END]);
		execve(execorder->comm, execorder->argsum, envp);
		perror(execorder->argsum[0]);
	}
	else
		waitpid(pidC, NULL, 0);
}
