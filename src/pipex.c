/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrussin <pgrussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:22:30 by pgrussin          #+#    #+#             */
/*   Updated: 2024/01/26 15:08:55 by pgrussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_exec(char *av[], t_struct *p_struct, char *envp[])
{
	int	i;

	i = 0;
	if (ft_pipe_init(av, p_struct, envp))
		return (error_h("mistake while filling struct", p_struct), 6);
	while (i <= 1)
	{
		p_struct->pid = fork();
		if (p_struct->pid < 0)
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
			return (error_h("erste Child dup2: ", p_struct), 4);
		if (dup2(p_struct->pipe_arr[1], 1) < 0)
			return (error_h("erste Chuild dup2: ", p_struct), 4);
		ft_close_all(p_struct);
		ft_execve(p_struct, p_struct->av1, p_struct->cmd1);
	}
	if (i == 1)
	{
		if (dup2(p_struct->pipe_arr[0], 0) < 0)
			return (error_h("zweite Child dup2: ", p_struct), 5);
		if (dup2(p_struct->fd_of, 1) < 0)
			return (error_h("zweite Child dup2: ", p_struct), 5);
		ft_close_all(p_struct); 
		ft_execve(p_struct, p_struct->av2, p_struct->cmd2);
	}
	return (perror("Error" ), 6);
}

int	ft_parent(t_struct *p_struct)
{
	int	wstatus;
	int	i;

	ft_close_all(p_struct);
	i = 0;
	if (!waitpid(-1, &wstatus, 0))
		i = 1;
	if (!waitpid(-1, &wstatus, 0))
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
