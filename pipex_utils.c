/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:10:37 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/05/05 22:20:51 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
		&& envp[i][3] == 'H')
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*ft_path_tester(char *totest, char *cmd)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(totest, ':');
	while (tab && tab[i])
	{
		tab[i] = ft_strjoin(tab[i], ft_strjoin("/", cmd));
		if (access(tab[i], R_OK) == 0)
			return (tab[i]);
		i++;
	}
	return (NULL);
}

char	*ft_fdtostr(int fd)
{
	char	*str;
	char	buffer[2];
	int		octet;

	str = NULL;
	octet = read(fd, buffer, 1);
	buffer[1] = 0;
	str = ft_strjoinfree(str, buffer);
	while (octet > 0)
	{
		octet = read(fd, buffer, 1);
		buffer[octet] = 0;
		str = ft_strjoinfree(str, buffer);
	}
	return (str);
}

int	ft_error(int argc, const char **argv, char **envp)
{
	char	**cmd;

	if (argc != 5)
	{
		ft_putstr_fd("number of arguments error\n", 1);
		return (-1);
	}
	if (access(argv[1], F_OK) == -1)
	{
		ft_putstr_fd("file1 error\n", 1);
		return (-1);
	}
	cmd = ft_split((char *)argv[2], ' ');
	if (ft_path_tester(ft_env(envp), cmd[0]) == NULL)
	{
		ft_putstr_fd("cmd1 error\n", 1);
		return (-1);
	}
	cmd = ft_split((char *)argv[3], ' ');
	if (ft_path_tester(ft_env(envp), cmd[0]) == NULL)
	{
		ft_putstr_fd("cmd2 error\n", 1);
		return (-1);
	}
	return (0);
}
