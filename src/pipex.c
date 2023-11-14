#include "pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	t_struct	*s_pipex;
	pid_t		pid;
	s_pipex = (t_struct *)malloc(sizeof(t_struct));
	if (ac != 5)
		return (perror("Mo Stinkt"), 5);
	if (ft_checker(av, s_pipex, envp) != 0)
		return (3);
	ft_exec(s_pipex);

	printf("%d\n", s_pipex->fd_if);
}
