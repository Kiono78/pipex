#include "pipex.h"

void	file_error(char *error_msg)
{
	perror(error_msg);
	exit(1);
}

int	return_error(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	return (1);
}

void	free_exit(t_pipex *pipex)
{
	int	i;

	while (pipex->paths[i])
		free(pipex->paths[i]);
	free(pipex);
	exit(1);
}