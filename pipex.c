#include "pipex.h"

int	open_file(char *file_name, int	rights)
{
	int	fd;

	fd = open(file_name, rights, 0644);
	if (fd < 0)
		file_error(file_name);
	return (fd);
}

int main(int argc, char **argv)
{
	t_pipex	pipex;

	//No error follows on windows
	if (argc != 5)
		return (arg_error(ARG_ERROR));
	pipex.fd[0] = open_file(argv[1], O_RDONLY);
	//could not be tested on windows
	pipex.fd[1] = open_file(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR);
	return (0);
}