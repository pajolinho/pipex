#include "pipex.h"
static char	**ft_extract_path(char **envp)
{
	char	**path;
	int		cnt;

	cnt = -1;
	while (envp[++cnt])
	{
		if (!ft_memcmp(envp[cnt], "PATH=", 5))
		{
			path = ft_split(&envp[cnt][5], ':');
			return (path);
		}	
	}
	return (NULL);
}

int	ft_pipe_init(char *av[], t_struct *p_struct, char *envp[])
{
	ft_init_all(p_struct);
	p_struct->fd_if = open(av[1], O_RDONLY);
	p_struct->fd_of = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (p_struct->fd_if == -1 || p_struct->fd_of == -1)
		return (error_h("Check the Files", p_struct), 4);
	p_struct->env = envp;
	p_struct->path = ft_extract_path(envp);
	p_struct->av1 = ft_split(av[2], ' ');
	p_struct->av2 = ft_split(av[3], ' '); 
	p_struct->cmd1 = ft_strjoin("/", p_struct->av1[0]);
	p_struct->cmd2 = ft_strjoin("/", p_struct->av2[0]);
	if (p_struct->path == NULL || p_struct->av1 == NULL || p_struct->av2 == NULL || 
		p_struct->cmd1 == NULL || p_struct->cmd2 == NULL)
		return (error_h("mistake in struct", p_struct), 6);
	if (pipe(p_struct->pipe_arr) != 0)
		return (error_h("do ur own plumbin", p_struct), 1312);
	return (0);
}

void	ft_init_all(t_struct *p_struct)
{
	p_struct->cmd1 = NULL;
	p_struct->cmd2 = NULL;
	p_struct->path = NULL;
	p_struct->av1 = NULL;
	p_struct->av2 = NULL;
}

int	ft_exec(char *av[], t_struct *p_struct, char *envp[])
{
	int	i;

	i = 0;
	if (ft_pipe_init(av, p_struct, envp))
		return(error_h("mistake while filling struct", p_struct), 6);
	while (i <= 1)
	{
		p_struct->pid = fork();
		if (p_struct->pid <  0)
			return (perror("fork: "), 3);
		if (p_struct->pid == 0)
			ft_child(p_struct, i);
		i++;
	}
	return (ft_parent(p_struct));
}

int	ft_child(t_struct *p_struct, int i)
{	
	if (i == 0)
	{
		if (dup2(p_struct->fd_if, 0) < 0)
			return (perror("dup2: "), 4);	
		if (dup2(p_struct->pipe_arr[1], 1) < 0)
			return (perror("dup2: "), 4);
		ft_close_all(p_struct);
		ft_execve(p_struct, p_struct->av1, p_struct->cmd1);
	}
	if (i == 1)
	{
		if (dup2(p_struct->pipe_arr[0], 0) < 0)
			return (perror("dup2: "), 4);	
		if (dup2(p_struct->fd_of, 1) < 0)
			return (perror("dup2: "), 4);	
		ft_close_all(p_struct); 
		ft_execve(p_struct, p_struct->av2, p_struct->cmd2);	
	}
	return (perror("ficken" ), 6);
}

int	ft_parent(t_struct *p_struct)
{
	int	wstatus;
	int	i;
	
	ft_close_all(p_struct);
	i = 0;
	
	if(!waitpid(-1, &wstatus, 0))
		i = 1;
	if(!waitpid(-1, &wstatus, 0))
		i = 2;
	return (i);
}

void	ft_execve(t_struct *p_struct, char **av, char *cmd)
{
	int		i;
	char	*temp;
	
	i = 0;
	temp = ft_strjoin("./", av[0]);
	if (!temp)
		error_h("mistake in execve strjoin", p_struct);
	if (access(temp, F_OK))
	{
		free(temp);
		temp = ft_strjoin(p_struct->path[i], cmd);
		if (!temp)
			error_h("mistake in execve strjoin", p_struct);
		while (p_struct->path[++i] != NULL && access(temp, F_OK) != 0)
		{
			free(temp);
			temp = ft_strjoin(p_struct->path[i], cmd);
		}
		if (p_struct->path[i] == NULL)
			error_h("path from struct not right", p_struct);
	}
	execve(temp, av, p_struct->env);
}


void	ft_close_all(t_struct *p_struct)
{
	close(p_struct->fd_of);
	close(p_struct->fd_if);
	close(p_struct->pipe_arr[0]);
	close(p_struct->pipe_arr[1]);
}
