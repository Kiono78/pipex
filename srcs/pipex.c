/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:06:51 by bterral           #+#    #+#             */
/*   Updated: 2022/02/04 12:52:43 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_paths(char **envp)
{
	char			**output;
	int				i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	if (envp[i])
		output = ft_split(&envp[i][5], ':');
	else
		output = NULL;
	return (output);
}

int	open_file(char *file_name, int rights)
{
	int	fd;

	fd = open(file_name, rights, 0644);
	if (fd < 0)
		perror_exit(file_name);
	return (fd);
}

int main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		return (return_error(ARG_ERROR));
	pipex.infile = open_file(argv[1], O_RDONLY);
	pipex.outfile = open_file(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR);
	if (pipe(pipex.fd) == -1)
		return (return_error(PIPE_ERROR));
	pipex.paths = get_paths(envp);
	if (pipex.paths == NULL)
		return (return_error(FAIL_PATHS));
	execute_commands(&pipex, argv, envp);
	if (close(pipex.fd[0]) == -1)
		perror_exit(CLOSE_FAILED);
	if (close(pipex.fd[1]) == -1)
		perror_exit(CLOSE_FAILED);
	if (waitpid(pipex.pid1, NULL, 0) == -1)
		perror_exit(WAITPID_FAILED);
	if (waitpid(pipex.pid2, NULL, 0) == -1)
		perror_exit(WAITPID_FAILED);
	return (0);
}
