/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrussin <pgrussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:04:53 by pgrussin          #+#    #+#             */
/*   Updated: 2024/01/26 15:07:14 by pgrussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	t_struct	*s_pipex;

	s_pipex = (t_struct *)malloc(sizeof(t_struct));
	if (!s_pipex)
		return (1);
	if (ac != 5)
	{
		free(s_pipex);
		return (error_h("wrong number of arguments", NULL), 2);
	}
	if (ft_exec(av, s_pipex, envp) != 0)
		return (error_h("ft_exec", s_pipex), 3);
	freeer(s_pipex);
	return (0);
}

void	error_h(char *error_msg, t_struct *p_struct)
{
	ft_putstr_fd(error_msg, 2);
	write(2, "\n", 1);
	if (p_struct)
	{
		ft_close_all(p_struct);
		freeer(p_struct);
	}
	exit(1);
}

void	freeer(t_struct *p_struct)
{
	int	i;

	i = -1;
	if (p_struct->path)
	{
		while (p_struct->path[++i])
			free(p_struct->path[i]);
		free(p_struct->path);
	}
	i = -1;
	if (p_struct->cmd1)
		free(p_struct->cmd1);
	if (p_struct->cmd2)
		free(p_struct->cmd2);
	freeer2(p_struct);
}

void	freeer2(t_struct *p_struct)
{
	int	i;

	i = -1;
	if (p_struct->av1)
	{
		while (p_struct->av1[++i])
			free(p_struct->av1[i]);
		free(p_struct->av1);
	}
	i = -1;
	if (p_struct->av2)
	{
		while (p_struct->av2[++i])
			free(p_struct->av2[i]);
		free(p_struct->av2);
	}
	free(p_struct);
}
