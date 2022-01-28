#include "pipex.h"

int	open_file(char *file_name, int	rights)
{
	int	fd;

	fd = open(file_name, rights, 0644);
	if (fd < 0)
		file_error(file_name);
	return (fd);
}

char	**get_paths(char **envp)
{
	char			**output;
	int				i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	output = ft_split(&envp[i][5], ':');
	return (output);
}

char	*get_cmd(t_pipex	*pipex)
{
	char	*cmd_path;
	char	*tmp;
	int		path_bool;
	int		i;

	i = 0;
	// printf("pipex->paths[0] : %s", pipex->paths[i]);
	while(pipex->paths[i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		cmd_path = ft_strjoin(tmp, pipex->cmd_args[0]);
		free(tmp);
		path_bool = access(cmd_path, X_OK);
		//going to leak ?
		if (path_bool == 0)
			return (cmd_path);
		i++;
	}
	if (path_bool == 0)
		free(cmd_path);
	return (cmd_path);
}

void	execute_second_command(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		free_exit(pipex);
	if (pipex->pid2 == 0)
	{
		pipex->cmd_args = ft_split(argv[3], ' ');
		printf("test\n");
		printf("pipex->cmd_args[0] : %s\n", pipex->cmd_args[0]);
		pipex->cmd = get_cmd(pipex);
		printf("pipex->cmd : %s\n", pipex->cmd);
		printf("pipex->cmd_args[1] : %s\n", pipex->cmd_args[1]);
		dup2(pipex->fd[0], STDIN_FILENO);
		dup2(pipex->fd[1], 1);
		close(pipex->fd[1]);
		execve(pipex->cmd, &pipex->cmd_args[1], envp);
	}
}

void	execute_commands(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		free_exit(pipex);
	if (pipex->pid1 == 0)
	{
		
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		dup2(pipex->infile, 0);
		close(pipex->fd[1]);
		pipex->cmd_args = ft_split(argv[2], ' ');
		pipex->cmd = get_cmd(pipex);
		printf("pipex->cmd : %s\n", pipex->cmd);
		printf("pipex->cmd_args[0] : %s\n", pipex->cmd_args[0]);
		execve(pipex->cmd, pipex->cmd_args, envp);
	}
	// execute_second_command(pipex, argv, envp);
}

int main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		return (return_error(ARG_ERROR));
	pipex.infile = open_file(argv[1], O_RDONLY);
	// pipex.outfile = open_file(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR);
	pipex.channel = pipe(pipex.fd);
	if (pipex.channel == -1)
		return (return_error(PIPE_ERROR));
	pipex.paths = get_paths(envp);
	execute_commands(&pipex, argv, envp);
	waitpid(pipex.pid1, NULL, 0);
	// waitpid(pipex.pid2, NULL, 0);
	printf("test\n");
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	return (0);
}