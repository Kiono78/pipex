/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:06:51 by bterral           #+#    #+#             */
/*   Updated: 2022/02/14 15:17:25 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_paths(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

char	**get_paths(char **envp)
{
	char			**output;
	int				i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
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

	if (access(file_name, F_OK) == -1)
		ft_putendl_fd("Input file does not exists !", 1);
	else if (access(file_name, R_OK) == -1)
		ft_putendl_fd("No permission to read the input file!", 1);
	fd = open(file_name, rights, 0644);
	return (fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		return (return_error(ARG_ERROR));
	pipex.infile = open_file(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe(pipex.fd) == -1)
		return (return_error(PIPE_ERROR));
	pipex.paths = get_paths(envp);
	if (pipex.paths == NULL)
		return (return_error(FAIL_PATHS));
	execute_commands(&pipex, argv, argc, envp);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	if (waitpid(pipex.pid1, NULL, 0) == -1)
		perror_exit(WAITPID_FAILED);
	if (waitpid(pipex.pid2, NULL, 0) == -1)
		perror_exit(WAITPID_FAILED);
	free_paths(pipex.paths);
	return (0);
}
