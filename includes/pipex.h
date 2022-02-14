/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:58:08 by bterral           #+#    #+#             */
/*   Updated: 2022/02/14 13:32:18 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*ft_strlen*/
# include "libft.h"

/*perror*/
# include <stdio.h>

/*open*/
# include <fcntl.h>

/*exit*/
# include <stdlib.h>

/*write*/
# include <unistd.h>

# define ARG_ERROR "Expected format error is: ./pipex file1 cmd1 cmd2 file2"
# define PIPE_ERROR "Pipe creation failed"
# define CMD_ERROR "Command not found"
# define PID_ERROR "Fail to create process"
# define FAIL_PATHS "Could not retrieve the PATH variable correctly"
# define WAITPID_FAILED "Waiting for child(ren) processes(es) failed"
# define CLOSE_FAILED "Program failed to close a file descriptor"
# define DUP_FAILED "DUP function failed"
# define EXECVE_FAILED "command execution failed"
# define WRITE_ERROR "ERROR while retrieving/writing data from input/to STDOUT"
# define CMD_FAILED "Error while retrieving system commands"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		fd[2];
	char	**paths;
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd_args;
	char	*cmd;
}	t_pipex;

/*files and paths*/
char	**get_paths(char **envp);
int		open_file(char *file_name, int rights);
void	free_paths(char **strings);

/*Error functions*/
int		return_error(char *err_msg);
void	perror_exit(char *error_msg);

/*children processes*/
char	*get_cmd(t_pipex	*pipex);
void	execute_second_cmd(t_pipex *pipex, char **argv, int argc, char **envp);
void	execute_commands(t_pipex *pipex, char **argv, int argc, char **envp);

#endif