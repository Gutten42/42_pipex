/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:16:07 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/14 13:08:48 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*sec_strchr(const char *str, int srch)
{
	size_t	ind;

	ind = 0;
	if (!str)
		return (NULL);
	while (str[ind] != 0)
	{
		if (str[ind] == (char)srch)
			return ((char *)(str + ind));
		ind++;
	}
	if (str[ind] == 0)
	{
		if (str[ind] == (char)srch)
			return ((char *)(str + ind));
	}
	return (NULL);
}

static int	gnl_strlen(char *str)
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
