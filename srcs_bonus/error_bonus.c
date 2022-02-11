/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:59:01 by bterral           #+#    #+#             */
/*   Updated: 2022/02/10 14:19:23 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	perror_exit(char *error_msg)
{
	perror(error_msg);
	exit(1);
}

int	return_error(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	return (1);
}

int	open_file(char *file_name, int rights)
{
	int	fd;

	fd = open(file_name, rights, 0644);
	if (fd < 0)
		perror_exit(file_name);
	return (fd);
}
