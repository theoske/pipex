/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:38:34 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/04/20 16:37:54 by tkempf-e         ###   ########.fr       */
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

#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc != 4)
		return (0);
	if (execve(argv[1], argv[0], )
}
