/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:06:58 by bterral           #+#    #+#             */
/*   Updated: 2022/02/10 13:49:54 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	execute_second_command(t_pipex *pipex, char **argv, int argc, char **envp)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		perror_exit(PID_ERROR);
	if (pipex->pid2 == 0)
	{
		if (close(pipex->fd[1]) == -1)
			perror_exit(CLOSE_FAILED);
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			perror_exit(DUP_FAILED);
		if (dup2(pipex->outfile, 1) == -1)
			perror_exit(DUP_FAILED);
		pipex->cmd_args = ft_split(argv[3], ' ');
		pipex->cmd = get_cmd(pipex);
		if (open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC) == -1)
		pipex->outfile = open_file(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR);
		if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
			perror_exit(EXECVE_FAILED);
	}
}

void	execute_commands(t_pipex *pipex, char **argv, int argc, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		perror_exit(PID_ERROR);
	if (pipex->pid1 == 0)
	{
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			perror_exit(DUP_FAILED);
		if (close(pipex->fd[0]) == -1)
			perror_exit(CLOSE_FAILED);
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			perror_exit(DUP_FAILED);
		pipex->cmd_args = ft_split(argv[2], ' ');
		pipex->cmd = get_cmd(pipex);
		if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
			perror_exit(EXECVE_FAILED);
	}
	execute_second_command(pipex, argv, argc, envp);
}
