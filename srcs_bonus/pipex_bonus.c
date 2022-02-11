/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:06:51 by bterral           #+#    #+#             */
/*   Updated: 2022/02/11 16:34:44 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

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

int	get_here_doc(t_pipex *pipex, char *argv[])
{
	char	*line;
	int		len;

	if (pipe(pipex->fd) == -1)
		perror_exit(PIPE_ERROR);
	line = NULL;
	len = ft_strlen(argv[2]);
	while (1)
	{
		ft_putstr_fd("pipex heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(line, argv[2], len) && line[len] == '\n')
			break ;
		if (write(pipex->fd[1], line, ft_strlen(line)) == -1)
			perror_exit(WRITE_ERROR);
		free(line);
	}
	free(line);
	close(pipex->fd[1]);
	return (pipex->fd[0]);
}

void	heredoc_infile(t_pipex *pipex, char *argv[], int argc)
{
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		pipex->infile = get_here_doc(pipex, argv);
		pipex->here_doc = 1;
	}
	else
	{
		pipex->infile = open_file(argv[1], O_RDONLY);
		pipex->here_doc = 0;
	}
	pipex->argc = argc;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		argv_count;

	if (!argv[1])
		return (return_error("No Argument found!"));
	heredoc_infile(&pipex, argv, argc);
	if (argc < (5 + pipex.here_doc))
		return (return_error(ARG_ERROR));
	pipex.paths = get_paths(envp);
	if (pipex.paths == NULL)
		return (return_error(FAIL_PATHS));
	pipex.input = read_input(&pipex);
	argv_count = 2 + pipex.here_doc;
	while ((argv_count) < (argc - 1))
	{
		pipex.input = execute_cmd(&pipex, argv, envp, argv_count);
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
