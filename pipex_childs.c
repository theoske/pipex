/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:20:00 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/05/05 22:20:46 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(const char **argv, int *fd, char **envp)
{
	int		fdo;
	char	*path;
	char	**cmd;

	path = ft_env(envp);
	cmd = ft_split((char *)argv[2], ' ');
	fdo = open(argv[1], O_RDONLY);
	path = ft_path_tester(path, cmd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fdo, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fdo);
	execve(path, cmd, envp);
}

void	ft_child2(const char **argv, int *fd, int *fd2, char **envp)
{
	char	**cmd2;
	char	*path;

	cmd2 = ft_split(argv[3], ' ');
	path = ft_path_tester(ft_env(envp), cmd2[0]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd2[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd2[1]);
	close(fd2[0]);
	execve(path, cmd2, envp);
}
