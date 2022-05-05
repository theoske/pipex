/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 22:03:51 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/05/05 22:09:39 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

size_t		ft_strlen(const char *s);
static int	ft_nbwords(char const *s, char c);
static char	**ft_tab(char	**tab, char	const *s, char c, int nb_word);
static char	**ft_malloc_tab2d(char const *s, char c);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_env(char **envp);
char		*ft_path_tester(char *totest, char *cmd);
char		*ft_line(char *line, char *buffer, int octet, int fd);
char		*ft_strjoinfree(char *s1, char *s2);
char		*ft_fdtostr(int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_child(const char **argv, int *fd, char **envp);
void		ft_child2(const char **argv, int *fd, int *fd2, char **envp);
int			ft_error(int argc, const char **argv, char **envp);
int			main(int argc, const char **argv, char **envp);

#endif