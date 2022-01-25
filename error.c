#include "pipex.h"

void	file_error(char *error_msg)
{
	perror(error_msg);
	exit(1);
}

int	arg_error(char *err_msg)
{
	perror(err_msg);
	return (1);
}