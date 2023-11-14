#include "pipex.h"
static char	**ft_extract_path(char **envp)
{
	char	**path;
	int		cnt;

	cnt = -1;
	while (envp[++cnt])
	{
		if (memcmp(envp[cnt], "PATH=", 5 == 0))
		{
			path = ft_split(envp[cnt], ';');
			return (path);
		}
			
	}
	return (NULL);
}
int	ft_checker(char *av[], t_struct *p_struct, char *envp[])
{

	p_struct->fd_if = open(av[1], O_RDONLY);
	p_struct->fd_of = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (p_struct->fd_if == -1 || p_struct->fd_of == -1)
	{
		return (perror("HALT STOP"), 1);
	}
	p_struct->env = envp;
	p_struct->path = ft_extract_path(envp);
	p_struct->cmd1 = strdup(av[2]);
	p_struct->cmd2 = strdup(av[3]);
	if (pipe(p_struct->pipe_arr) != 0)
		return (perror("do ur own plumbin"), 2);
	return (0);
}

int	ft_exec(t_struct p_struct)
{
	
}
