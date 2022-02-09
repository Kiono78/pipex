/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:06:51 by bterral           #+#    #+#             */
/*   Updated: 2022/02/09 16:40:15 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	free_paths(char **strings)
{
	int i;
	
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

	fd = open(file_name, rights, 0644);
	if (fd < 0)
		perror_exit(file_name);
	return (fd);
}

int	get_here_doc(t_pipex *pipex, char *argv[])
{
	char	*line;
	
	if (pipe(pipex->fd) == -1)
		perror_exit(PIPE_ERROR);
	line = NULL;
	while (1)
	{
		ft_putstr_fd("pipex heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		//segfautl en dessous ??
		if (!ft_strncmp(line, argv[2], ft_strlen(argv[2])))
			break;
		if (write(pipex->fd[1], line, ft_strlen(line)) == -1)
			perror_exit(WRITE_ERROR);
		free(line);
	}
	free(line);
	close(pipex->fd[1]);
	return (pipex->fd[0]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		argv_count;

	if (argc < 5)
		return (return_error(ARG_ERROR));
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		pipex.infile = get_here_doc(&pipex,argv);
		pipex.here_doc = 1;
	}
	else
	{
		pipex.infile = open_file(argv[1], O_RDONLY);
		pipex.here_doc = 0;
	}
	pipex.argc = argc;
	pipex.paths = get_paths(envp);
	if (pipex.paths == NULL)
		return (return_error(FAIL_PATHS));
	pipex.input = read_input(&pipex);
	argv_count = 2 + pipex.here_doc;
	while ((argv_count) < (argc - 1))
	{
		pipex.input = execute_command(&pipex, argv, envp, argv_count);
		argv_count++;
	}
	while (argv_count > (2 + pipex.here_doc))
	{
		wait(0);
		argv_count--;
	}
	write_output(&pipex);
	free_paths(pipex.paths);
	return (0);
}
