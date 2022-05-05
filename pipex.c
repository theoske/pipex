/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:38:34 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/05/05 20:51:14 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	ft_nbwords(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_word;

	if (s[0] == '\0')
		return (0);
	i = 0;
	while (s[i] == c && s[i])
		i++;
	nb_word = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c && s[i - 1] != c)
			nb_word++;
		i++;
	}
	if (s[i] == '\0' && s[i - 1] != c)
		nb_word++;
	return (nb_word);
}

static char	**ft_tab(char	**tab, char	const *s, char c, int nb_word)
{
	int	i;
	int	j;
	int	compt;

	i = 0;
	j = 0;
	while (s[i] && j < nb_word)
	{
		while (s[i] == c && s[i])
			i++;
		compt = 0;
		while (s[i] != c && s[i++])
			compt ++;
		if (s[i - 1] != c)
		{
			tab[j] = malloc(sizeof(char) * (compt + 1));
			if (!tab)
				return (0);
			tab[j][compt] = '\0';
		}
		j++;
	}
	return (tab);
}

static char	**ft_malloc_tab2d(char const *s, char c)
{
	size_t			nb_word;
	char			**tab;

	nb_word = ft_nbwords(s, c);
	if (s[0] == '\0' && nb_word == 0)
	{
		tab = (char **)malloc(sizeof(char *));
		tab[0] = NULL;
		return (tab);
	}
	tab = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (0);
	tab[nb_word] = 0;
	tab = ft_tab(tab, s, c, nb_word);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	index[2];
	char			**tab;

	tab = ft_malloc_tab2d(s, c);
	if (!tab)
		return (NULL);
	i = 0;
	index[0] = 0;
	while (tab[index[0]] && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		index[1] = 0;
		while (s[i] != c && s[i])
		{
			tab[index[0]][index[1]] = s[i];
			index[1]++;
			i++;
		}
		index[0]++;
	}
	return (tab);
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

char	*ft_line(char *line, char *buffer, int octet, int fd)
{
	while (buffer[0] != '\n' && octet > 0)
	{
		octet = read(fd, buffer, 1);
		buffer[octet] = '\0';
		line = ft_strjoin(line, buffer);
	}
	return (line);
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
	path = ft_env(envp);
	path = ft_path_tester(path, cmd2[0]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd2[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd2[1]);
	close(fd2[0]);
	execve(path, cmd2, envp);
}

int	ft_arg_error(void)
{
	ft_putstr_fd("Wrong number of arguments\n", 1);
	return (-1);
}

int	main(int argc, const char **argv, char **envp)
{
	int		fd[3][2];
	int		pid[2];
	char	*path;

	if (argc != 5)
		return (ft_arg_error());
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
