#include "pipex.h"

//printf("command not found: %s\n", exec_order->argsum[0]);

static void	execfree(t_execord *exec_order)
{
	int	ind;
	
	if (exec_order->free && exec_order->comm)
		free(exec_order->comm);
	ind = 0;
	while (exec_order->argsum[ind])
	{
		free(exec_order->argsum[ind]);
		ind++;	
	}
	free(exec_order->argsum);
}

static void	get_execord(char *command, char **paths, t_execord *result)
{
	char		**complus;
	char		*last_bar;
	
	complus = ft_split(command, ' ');
	last_bar = ft_strrchr(complus[0], '/');
	if (last_bar)
	{
		result->comm = command;
		if (access(result->comm, F_OK) < 0)
		 	result->comm = NULL;
		result->argsum = complus;
		last_bar = ft_strdup(last_bar + sizeof(char));
		free(complus[0]);
		result->argsum[0] = last_bar;
		result->free = 0;
	}
	else
	{
		result->comm = search_comm(complus[0], paths);
		result->argsum = complus;
		result->free = 1;
	}
}

void	exec_comm(t_envir *env, int ind, int rfd, int wfd)
{
	t_execord	exec_order;

	if (!env->argv[ind] || !env->argv[ind][0])
		write(1, "No esiste eso\n", 14);
	else
	{
		get_execord(env->argv[ind], env->paths, &exec_order);
		if (!exec_order.comm)
		{
			if (exec_order.free)
				write(1, "No esiste ese comando\n", 22);
			else
				write(1, "No esiste ese archivo\n", 22);
		}
		else
			exec(&exec_order, rfd, wfd, env->envp);
		execfree(&exec_order);
	}
	close(rfd);
	close(wfd);
}
