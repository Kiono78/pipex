/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:59:01 by bterral           #+#    #+#             */
/*   Updated: 2022/02/11 16:57:01 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	argument_error(int argc, char *argv[], t_pipex *pipex)
{
	if (!argv[1])
		return (1);
	if (argc < 5)
		return (1);
	heredoc_infile(pipex, argv, argc);
	if (argc < (5 + pipex->here_doc))
		return (1);
	return (0);
}

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
