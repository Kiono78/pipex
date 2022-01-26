#ifndef PIPEX_H
# define PIPEX_H

/*ft_strlen*/
# include "libft/libft.h"

/*perror*/
# include <stdio.h>

/*open*/
#include <fcntl.h>

/*exit*/
# include <stdlib.h>

/*write*/
# include <unistd.h>


# define ARG_ERROR "Expected format error is: ./pipex file1 cmd1 cmd2 file2"
# define PIPE_ERROR "Pipe creation failed"



typedef struct s_pipex
{
	int		channel;
	int		fd[2];
	char	**paths;
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd_args;
	char	*cmd;
}	t_pipex;




/*Error functions*/
int		return_error(char *err_msg);
void	file_error(char *error_msg);
void	free_exit(t_pipex *pipex);


#endif