/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:38:34 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/05/05 22:20:41 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	j = 0;
	i = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s1 && s1[i])
	{
		join[i] = *(char *)(s1 + i);
		i++;
	}
	while (s2[j])
	{
		join[i + j] = *(char *)(s2 + j);
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	j = 0;
	i = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s1 && s1[i])
	{
		join[i] = *(char *)(s1 + i);
		i++;
	}
	while (s2[j])
	{
		join[i + j] = *(char *)(s2 + j);
		j++;
	}
	join[i + j] = '\0';
	free(s1);
	return (join);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	while (s[i])
	{
		write(fd, &(s[i]), 1);
		i++;
	}
}

int	main(int argc, const char **argv, char **envp)
{
	int		fd[3][2];
	int		pid[2];
	char	*path;

	if (ft_error(argc, argv, envp) == -1)
		return (-1);
	pipe(fd[0]);
	pid[0] = fork();
	if (pid[0] == 0)
		ft_child(argv, fd[0], envp);
	pipe(fd[1]);
	pid[1] = fork();
	if (pid[1] == 0)
		ft_child2(argv, fd[0], fd[1], envp);
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][1]);
	path = ft_fdtostr(fd[1][0]);
	close(fd[1][0]);
	fd[2][0] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_putstr_fd(path, fd[2][0]);
	close(fd[2][0]);
	waitpid(pid[0], 0, 0);
	waitpid(pid[1], 0, 0);
	return (0);
}
