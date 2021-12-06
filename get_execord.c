
#include "pipex.h"

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
