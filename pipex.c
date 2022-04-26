/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:38:34 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/04/26 21:58:05 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
| : The pipe operator, it passes the output of one command as input to another.
A command built from the pipe operator is called a pipeline.

< : Gives input to a command.
command < file.txt
The above will execute command on the contents of file.txt.

<> : same as above, but the file is open in read+write mode instead of read-only:
command <> file.txt

> : Directs the output of a command into a file.
command > out.txt
The above will save the output of command as out.txt. 
If the file exists, its contents will be overwritten and 
if it does not exist it will be created.
*/

/*
./pipex file1 "cmd1" "cmd2" file2
< file1 cmd1 | cmd2 > file2
pipe entre cmd1 et cmd2.
resultat de la cmd1 est l'entree de cmd2.
resultat de la deuxieme est entree dans file2.
*/

/*
void perror(const char *str) : affiche le message d'erreur a la suite de str.

char *strerror(int errnum) : renvoie l'erreur dans une chaine. Prend le numero de l'erreur en parametre (en general errno).

int access(const char *pathname, int mode) : verifie l'acces a un fichier avec mode au choix (F/R/W/X_OK). return 0 if success. 
-1 if failure and sets errno correctly.

int dup(int oldfd) : return new file descriptor.

int dup2(int oldfd, int newfd) : comme dup mais au lieu d'utiliser le fd du numero le plus bas, il utilise celui
de numero newfd.

int execve(const char *filepath, char *const argv[], char *const envp[]) : execute le programme de filepath.
argv sont les arguments a passer au programme. envp sont les variables d'env, se termine par NULL.
Ne retourne rien en cas de succes.

pid_t fork(void) : cree un nouveau processus (=child) en dupliquant celui qui est appelé (=parent).
child has unique process ID.

int pipe(int pipefd[2]) : cree un tunnel unidirectionnel de données permettant une communication inter-processus. 
pipe[0] est le fd de lecture et pipe[1] le fd d'ecriture. 0 retourner en cas de succes.

int unlink(const char *pathname) : supprime un nom du systeme de fichier
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//tester chaque path avec access et lancer cmd avec celui aui fonctionne

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
		tab[i] = ft_strjoin(tab[i], cmd);
		if (access(tab[i], R_OK) == 0)
			return (tab[i]);
		i++;
	}
	return (NULL);
}
//il faut maintenant faire les pipes
int	main(int argc, const char **argv, char **envp)
{
	char	*path;
	char	**cmd;
	int		pid;
	int		i;

	i = 2;
	pid = 0;
	path = ft_env(envp);
	while (i < argc - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			cmd = ft_split(argv[i], ' ');
			path = ft_path_tester(path, ft_strjoin("/", cmd[0]));
			execve(path, cmd, envp);
		}
		i++;
	}
	return (0);
}
