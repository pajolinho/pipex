#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct	s_struct
{
	int	fd_if;
	int fd_of;
	char	*cmd1;
	char	*cmd2;
	int	pipe_arr[2];
	pid_t	pid[2];
	char	**env;
}	t_struct;
int	ft_checker(char *av[], t_struct *p_struct, char *envp[]);
#endif
