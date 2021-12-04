/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_comm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:45:56 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/01 20:21:59 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*search_comm(char *comm, char **paths)
{
	int		i;
	char	*ret;

	i = 0;
	while (paths[i])
	{
		ret = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(ret, comm);
		if (access(ret, F_OK) > -1)
			return (ret);
		free(ret);
		i++;
	}
	return (NULL);
}