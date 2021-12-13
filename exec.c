
#include "pipex.h"

void	exec(t_execord *execorder, int rfd, int *pip, char **envp)
{
	pid_t		pidC;

	pidC = fork();
	if (pidC == -1)
		perror("fork");
	else if (pidC == 0)
	{
		close(pip[RD_END]);
		dup2(rfd, STDIN_FILENO);
		close(rfd);
		dup2(pip[WR_END], STDOUT_FILENO);
		close(pip[WR_END]);
		if (execve(execorder->comm, execorder->argsum, envp) < 0)
		{
			perror(execorder->argsum[0]);
			exit (0);
		}
	}
	else
		waitpid(pidC, NULL, 0);
}
