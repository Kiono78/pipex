/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_processes_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:06:58 by bterral           #+#    #+#             */
/*   Updated: 2022/02/11 15:50:25 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

char	*get_cmd(t_pipex	*pipex)
{
	char	*cmd_path;
	char	*tmp;
	int		path_bool;
	int		i;

	i = 0;
	while (pipex->paths[i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		cmd_path = ft_strjoin(tmp, pipex->cmd_args[0]);
		free(tmp);
		path_bool = access(cmd_path, X_OK);
		if (path_bool == 0)
			return (cmd_path);
		i++;
	}
	if (path_bool == -1)
		perror_exit(CMD_ERROR);
	return (cmd_path);
}

void	open_outfile(t_pipex *pipex, char **argv, int argv_count)
{
	if (argv_count == (pipex->argc - 2) && pipex->here_doc == 0)
		pipex->outfile
			= open(argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (argv_count == (pipex->argc - 2) && pipex->here_doc == 1)
		pipex->outfile
			= open(argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
}

int	execute_cmd(t_pipex *pipex, char **argv, char **envp, int argv_count)
{
	open_outfile(pipex, argv, argv_count);
	if (pipe(pipex->fd) == -1)
		perror_exit(PIPE_ERROR);
	pipex->pid = fork();
	if (pipex->pid == -1)
		perror_exit(PID_ERROR);
	if (pipex->pid == 0)
	{
		if (close(pipex->fd[0]) == -1)
			perror_exit(CLOSE_FAILED);
		if (dup2(pipex->input, STDIN_FILENO) == -1)
			perror_exit(DUP_FAILED);
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			perror_exit(DUP_FAILED);
		pipex->cmd_args = ft_split(argv[argv_count], ' ');
		pipex->cmd = get_cmd(pipex);
		if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
			perror_exit(EXECVE_FAILED);
	}
	if (close(pipex->fd[1]) == -1)
		perror_exit(CLOSE_FAILED);
	return (pipex->fd[0]);
}

int	read_input(t_pipex *pipex)
{
	int		pipe_fd[2];
	int		bytes_read;
	char	buffer[1];

	if (pipe(pipe_fd) == -1)
		perror_exit(PIPE_ERROR);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(pipex->infile, buffer, 1);
		if (bytes_read == -1)
			perror_exit(INFILE_READ_FAILED);
		if (bytes_read == 1)
		{
			if (write(pipe_fd[1], buffer, 1) == -1)
				perror_exit(WRITE_ERROR);
		}
	}
	if (close(pipex->infile) == -1)
		perror_exit(CLOSE_FAILED);
	if (close(pipe_fd[1]) == -1)
		perror_exit(CLOSE_FAILED);
	return (pipe_fd[0]);
}

void	write_output(t_pipex *pipex)
{
	int		bytes_read;
	char	buffer[1];

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(pipex->input, buffer, bytes_read);
		if (bytes_read == -1)
			perror_exit(INFILE_READ_FAILED);
		if (bytes_read == 1)
		{
			if (write(pipex->outfile, buffer, 1) == -1)
				perror_exit(WRITE_ERROR);
		}
	}
	if (close(pipex->input) == -1)
		perror_exit(CLOSE_FAILED);
	if (close(pipex->outfile) == -1)
		perror_exit(CLOSE_FAILED);
}
