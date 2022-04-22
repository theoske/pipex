/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:38:34 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/04/22 21:12:04 by theo             ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	if (argc != 4)
		return (0);
	if (execve(argv[1], argv[0], )
}
