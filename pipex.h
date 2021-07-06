#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

void	*for_free(char **new1);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	define_path(char *argv_n, char **envp);
char	*ft_strjoin_slash(char const *s1, char const *s2);
char	**for_path(char **envp);
void	first_pipe(int fd[2], char **argv, char **envp);
void	second_pipe(int fd[2], char **argv, char **envp);
void	ft_error(char *str);
void	*for_free_int(int **arr, int argc);
void	first_pipes(int argc, char **argv, int **pipes);
void	last_pipes(int argc, char **argv, int **pipes);
void	middle_pipes(int argc, int i, int **pipes);
void	second_bonus(char **argv, char **envp);
void	tmp_file(char **argv);
void	first_pipe_bon(int fd[2], char **argv, char **envp);
void	second_pipe_bon(int fd[2], char **argv, char **envp);
void	which_pipe(int argc, char **argv, int **pipes, int i);
void	check_args(int argc, char **argv, char **envp);
int		**for_pipes(int argc);
void	for_end(int argc, int **pipes, int *pids);

#endif