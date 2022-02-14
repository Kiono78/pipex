/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:58:08 by bterral           #+#    #+#             */
/*   Updated: 2022/02/14 15:52:42 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

# define ARG_ERROR "Arguments provided are not valid!"
# define PIPE_ERROR "Pipe creation failed"
# define CMD_ERROR "Warning : Command not found\n"
# define PID_ERROR "Fail to create process"
# define FAIL_PATHS "Could not retrieve the PATH variable correctly"
# define WAITPID_FAILED "Waiting for child(ren) processes(es) failed"
# define CLOSE_FAILED "Program failed to close a file descriptor"
# define DUP_FAILED "DUP function failed"
# define EXECVE_FAILED "Command execution failed"
# define INFILE_READ_FAILED "Warning:An issue occured while reading the infile"
# define WRITE_ERROR "ERROR while retrieving/writing data from input/to STDOUT"
# define CMD_FAILED "Error while retrieving system commands"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**paths;
	int		input;
	int		fd[2];
	pid_t	pid;
	char	**cmd_args;
	char	*cmd;
	int		argc;
	int		here_doc;
}	t_pipex;

/*files and paths*/
char	**get_paths(char **envp);
int		open_file(char *file_name, int rights);
void	free_paths(char **strings);
void	heredoc_infile(t_pipex *pipex, char *argv[], int argc);

/*Error functions*/
int		return_error(char *err_msg);
void	perror_exit(char *error_msg);
int		argument_error(int argc, char *argv[], t_pipex *pipex);

/*children processes*/
char	*get_cmd(t_pipex	*pipex);
int		read_input(t_pipex *pipex);
int		execute_cmd(t_pipex *pipex, char **argv, char **envp, int argv_count);
void	write_output(t_pipex *pipex);
void	open_outfile(t_pipex *pipex, char **argv, int argv_count);

#endif