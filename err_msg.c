/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:40:32 by vguttenb          #+#    #+#             */
/*   Updated: 2021/12/14 13:45:52 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err_msg(char *err, char *filename)
{
	ft_putstr_fd("pipex: ", 1);
	ft_putchar_fd(ft_tolower(err[0]), 1);
	ft_putstr_fd(err + sizeof(char), 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(filename, 1);
}
