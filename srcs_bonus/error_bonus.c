/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:59:01 by bterral           #+#    #+#             */
/*   Updated: 2022/02/14 14:07:57 by bterral          ###   ########.fr       */
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
	if (write(2, error_msg, ft_strlen(error_msg)) == -1)
		perror_exit(WRITE_ERROR);
	exit(1);
}

int	return_error(char *err_msg)
{
	if (write(2, err_msg, ft_strlen(err_msg)) == -1)
		perror_exit(WRITE_ERROR);
	return (1);
}

int	open_file(char *file_name, int rights)
{
	int	fd;

	if (access(file_name, 'F_OK') == -1)
		ft_putendl_fd("Input file does not exists !", 1);
	else if (access(file_name, 'R_OK') == -1)
		ft_putendl_fd("No permission to read the input file!", 1);
	fd = open(file_name, rights, 0644);
	return (fd);
}
