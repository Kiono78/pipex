#include "pipex.h"

void	perror_exit(char *error_msg)
{
	perror(error_msg);
	exit(1);
}

int	return_error(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	return (1);
}
