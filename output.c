
#include "pipex.h"

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