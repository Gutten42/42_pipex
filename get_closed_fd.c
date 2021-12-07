/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closed_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:13:49 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/07 18:02:03 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	randomize_str(char *str, int size)
{
	while (size >= 0 && str[size] == 'z')
		size--;
	if (size < 0)
		return (0);
	str[size] += 1;
	while (str[++size])
		str[size] = '0';
	return (1);
}

static char	*get_random_str(void)
{
	char	*nofile;
	int		size;
	int		ind;
	
	size = 1;
	while (1)
	{
		nofile = (char *)malloc(sizeof(char) * (size + 1));
		nofile[size] = '\0';
		ind = 0;
		while (ind < size)
			nofile[ind++] = '0';
		while(1)
		{
			if (!nofile[size + 1] && access(nofile, F_OK) == -1)
				return (nofile);
			if (!randomize_str(nofile, size - 1))
				break ;
		}
		free(nofile);	
		size++;
	}
}

int	get_closed_fd(void)
{
	char	*nofile;
	int		ret;

	nofile = get_random_str();
	ret = open(nofile, O_RDONLY | O_CREAT, 0666);
	unlink(nofile);
	free(nofile);
	return (ret);
}