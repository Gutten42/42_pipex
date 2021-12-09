/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_comm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:45:56 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/08 20:32:41 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	gnl_strlen(char *str)
{
	int		size;

	size = 0;
	if (str)
		while (str[size])
			size++;
	return (size);
}

char	*gnl_strjoin(char *keeper, char *buffer)
{
	int		size;
	int		ind1;
	int		ind2;
	char	*result;

	ind1 = -1;
	ind2 = 0;
	size = gnl_strlen(keeper) + gnl_strlen(buffer);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (keeper)
		while (keeper[++ind1])
			result[ind1] = keeper[ind1];
	else
		ind1++;
	if (buffer)
		while (buffer[ind2])
			result[ind1++] = buffer[ind2++];
	result[ind1] = '\0';
	free (keeper);
	return (result);
}

char	*search_comm(char *comm, char **paths)
{
	int		i;
	char	*ret;

	i = 0;
	while (paths[i])
	{
		ret = ft_strjoin(paths[i], "/");
		ret = gnl_strjoin(ret, comm);
		if (access(ret, F_OK) > -1)
			return (ret);
		free(ret);
		i++;
	}
	return (NULL);
}