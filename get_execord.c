
#include "pipex.h"

void	get_execord(char *command, char **paths, t_execord *result)
{
	char		**complus;
	char		*last_bar;
	
	complus = ft_split(command, ' ');
	last_bar = ft_strrchr(complus[0], '/');
	write(1, "hey\n", 4);
	if (last_bar)
	{
		result->comm = command;
		if (access(result->comm, F_OK) < 0)
		 	result->comm = NULL;
		result->argsum = complus;
		free(complus[0]);
		result->argsum[0] = ft_strdup(last_bar + sizeof(char));
		result->free = 0;
	}
	else
	{
		result->comm = search_comm(complus[0], paths);
		result->argsum = complus;
		result->free = 1;
	}
}
