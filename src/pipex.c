#include "pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	t_struct	*s_pipex;
	
	s_pipex = (t_struct *)malloc(sizeof(t_struct));
	if (!s_pipex)
		return (1);
	if (ac != 5)
		return (error_h("wrong number of arguments", NULL), 2);
	if (ft_exec(av, s_pipex, envp) != 0)
		return (error_h("ft_exec", s_pipex), 3);
	freeer(s_pipex);
	return (0);
}

void	error_h(char *error_msg, t_struct *p_struct)
{
	ft_putstr_fd(error_msg, 2);
	ft_close_all(p_struct);
	if (p_struct)
		freeer(p_struct);
	exit(1);
}

void	freeer(t_struct *p_struct)
{
	if (p_struct->path)
		free(p_struct->path);
	if (p_struct->cmd1)
		free(p_struct->cmd1);
	if (p_struct->cmd2)
		free(p_struct->cmd2);
	if (p_struct->av1)
		free(p_struct->av1);
	if (p_struct->av2)
		free(p_struct->av2);
}
