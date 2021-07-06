#include "pipex.h"

void	first_pipe(int fd[2], char **argv, char **envp)
{
	int	file1;

	close(fd[0]);
	file1 = open(argv[1], O_RDONLY, 0644);
	if (file1 == -1)
	{
		perror(argv[1]);
		exit (1);
	}
	if (dup2(file1, 0) == -1)
		ft_error(strerror(errno));
	if (dup2(fd[1], 1) == -1)
		ft_error(strerror(errno));
	close(fd[1]);
	close(file1);
	define_path(argv[2], envp);
}

void	second_pipe(int fd[2], char **argv, char **envp)
{
	int	file2;

	close(fd[1]);
	file2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2 == -1)
	{
		perror(argv[4]);
		exit (2);
	}
	if (dup2(fd[0], 0) == -1)
		ft_error(strerror(errno));
	if (dup2(file2, 1) == -1)
		ft_error(strerror(errno));
	close(fd[0]);
	close(file2);
	define_path(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		ft_error("Input error, try format:\n./pipex f1 c1 c2 f2\n");
	if (pipe(fd) == -1)
		ft_error(strerror(errno));
	pid1 = fork();
	if (pid1 < 0)
		ft_error(strerror(errno));
	if (pid1 == 0)
		first_pipe(fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		ft_error(strerror(errno));
	if (pid2 == 0)
		second_pipe(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
