#include "pipex.h"
static char	**ft_extract_path(char **envp)
{
	char	**path;
	int		cnt;

	cnt = -1;
	while (envp[++cnt])
	{
		if (ft_memcmp(envp[cnt], "PATH=", 5))
		{
			path = ft_split(envp[cnt], ';');
			return (path);
		}	
	}
	return (NULL);
}

int	ft_pipe_init(char *av[], t_struct *p_struct, char *envp[])
{

	p_struct->fd_if = open(av[1], O_RDONLY);
	p_struct->fd_of = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (p_struct->fd_if == -1 || p_struct->fd_of == -1)
		return (perror("Check the Files"), 1);
	p_struct->env = envp;
	p_struct->path = ft_extract_path(envp);
	p_struct->cmd1 = strdup(av[2]);
	p_struct->cmd2 = strdup(av[3]);
	if (pipe(p_struct->pipe_arr) != 0)
		return (perror("do ur own plumbin"), 2);
	return (0);
}

int	ft_exec(char *av[], t_struct *p_struct, char *envp[])
{
	int	i;

	i = 0;
	//struct uebernommen?
	if (!ft_pipe_init(av, p_struct, envp))
		return(1);
	while (i <= 1)
	{
		p_struct->pid = fork();
		if (p_struct->pid <  0)
			return (perror("fork: "), 3);
		if (p_struct->pid == 0)
			ft_child(p_struct, i);
		i++;
	}
	return (ft_parent());
}

int	ft_child(t_struct *p_struct, int i)
{	
	if (i == 0)
	{
		if (dup2(p_struct->fd_if, 0) < 0)
			return (perror("dup2: "), 4);	
		if (dup2(p_struct->pipe_arr[0], 1) < 0)
			return (perror("dup2: "), 4);
		ft_close_all(p_struct);
		ft_execve(p_struct, p_struct->cmd1);
	}
	if (i == 1)
	{
		if (dup2(p_struct->pipe_arr[1], 0) < 0)
			return (perror("dup2: "), 4);	
		if (dup2(p_struct->fd_of, 1) < 0)
			return (perror("dup2: "), 4);	
		ft_close_all(p_struct); 
		ft_execve(p_struct, p_struct->cmd2);	
	}
	return (perror("ficken" ), 6);
}

int	ft_parent(void)
{
	int	wstatus;
	int	i;
	
	i = 0;
	if(!waitpid(-1, &wstatus, 0))
		i = 1;
	if(!waitpid(-1, &wstatus, 0))
		i = 2;
	return (i);
}

void	ft_execve(t_struct *p_struct, char *cmd)
{
	int		i;
	char	**av;
	char	*temp;
	
	i = 0;
	temp = ft_strjoin("./", cmd);
	if (!temp)
	{
		//error_h()
		exit(1);
	}
	if (access(temp, F_OK))
	{
		free(temp);
		temp = ft_strjoin(p_struct->path[i], cmd);
		while (p_struct->path[i] != NULL && access(temp, F_OK) != 0)
		{
			free(temp);
			temp = ft_strjoin(p_struct->path[i], cmd);
			i++;
		}
		if (p_struct->path[i] == NULL)
		{
		//	freeer();
			exit(1);
		}
	}
	av = ft_split(cmd, ' ');
	execve(temp, av, p_struct->env);
}


void	ft_close_all(t_struct *p_struct)
{
	close(p_struct->fd_of);
	close(p_struct->fd_if);
	close(p_struct->pipe_arr[0]);
	close(p_struct->pipe_arr[1]);
}
