#include "pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	t_struct	*s_pipex;
	
	s_pipex = (t_struct *)malloc(sizeof(t_struct));
	if (ac != 5)
		return (perror("Arguments wrong:"), 5);
	if (ft_exec(av, s_pipex, envp) != 0)
		return (2);
	printf("%d\n", s_pipex->fd_if);
}
