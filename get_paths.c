/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:01:59 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/01 20:16:11 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	int		i;
	char	*paths;
	char	**result;

	i = 0;
	while (envp[i])
	{
		paths = ft_strnstr(envp[i], "PATH=", 5);
		if (paths)
			return (ft_split(paths + sizeof(char) * 5, ':'));
		i++;
	}
	result = (char**)malloc(sizeof(char*) * 2);
	result[0] = (char)malloc(sizeof(char));
	result[0][1] = '\0';
	result[1] = NULL;
	return (result);
}