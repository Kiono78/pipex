#ifndef PIPEX_H
# define PIPEX_H

/*perror*/
# include <stdio.h>

/*open*/
#include <fcntl.h>

/*exit*/
# include <stdlib.h>

# define ARG_ERROR "Expected format error is: ./pipex file1 cmd1 cmd2 file2"


typedef struct s_pipex
{
	int		fd[2];
}	t_pipex;




/*Error functions*/
int		arg_error(char *err_msg);
void	file_error(char *error_msg);

#endif