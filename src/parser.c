/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrussin <pgrussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:05:30 by pgrussin          #+#    #+#             */
/*   Updated: 2023/11/21 15:22:40 by pgrussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (p_struct->path == NULL || p_struct->av1 == NULL || 
		p_struct->av2 == NULL || p_struct->cmd1 == NULL || 
		p_struct->cmd2 == NULL)
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

void	ft_close_all(t_struct *p_struct)
{
	close(p_struct->fd_of);
	close(p_struct->fd_if);
	close(p_struct->pipe_arr[0]);
	close(p_struct->pipe_arr[1]);
}
