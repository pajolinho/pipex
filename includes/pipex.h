/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrussin <pgrussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:24:18 by pgrussin          #+#    #+#             */
/*   Updated: 2024/01/26 15:09:12 by pgrussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft_all/srcs/ft_printf/includes/ft_printf.h"
# include "../libft_all/srcs/libft/libft.h"

typedef struct s_struct
{
	int		fd_if;
	int		fd_of;
	char	**av1;
	char	**av2;
	char	**path;
	char	*cmd1;
	char	*cmd2;
	int		pipe_arr[2];
	pid_t	pid;
	char	**env;
}	t_struct;

int		ft_pipe_init(char *av[], t_struct *p_struct, char *envp[]);
int		ft_exec(char *av[], t_struct *p_struct, char *envp[]);
int		ft_child(t_struct *p_struct, int i);
int		ft_parent(t_struct *p_struct);
void	ft_close_all(t_struct *p_struct);
void	error_h(char *error_msg, t_struct *p_struct);
void	freeer(t_struct *p_struct);
void	ft_init_all(t_struct *p_struct);
void	ft_execve(t_struct *p_struct, char **av, char *cmd);
void	freeer2(t_struct *p_struct);
#endif
