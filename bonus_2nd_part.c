#include "pipex.h"

void	tmp_file(char **argv)
{
	int		tmp;
	int		ret;
	char	buf[255];

	tmp = open("temp_del", O_RDWR | O_CREAT, 0644);
	if (tmp == -1)
		exit(EXIT_FAILURE);
	ret = 1;
	while (ret)
	{
		write(1, "> ", 2);
		ret = read(0, buf, 254);
		buf[ret] = '\0';
		if (strncmp(ft_strjoin(argv[2], "\n"), buf, ft_strlen(buf)) == 0)
			break ;
		write(tmp, buf, ft_strlen(buf));
	}
}

void	first_pipe_bon(int fd[2], char **argv, char **envp)
{
	int		tmp;

	close(fd[0]);
	tmp_file(argv);
	tmp = open("temp_del", O_RDONLY, 0644);
	if (tmp == -1)
	{
		perror("temp_del");
		exit (1);
	}
	if (dup2(tmp, 0) == -1)
		ft_error(strerror(errno));
	if (dup2(fd[1], 1) == -1)
		ft_error(strerror(errno));
	close(fd[1]);
	close(tmp);
	if (unlink("temp_del") == -1)
		ft_error(strerror(errno));
	define_path(argv[3], envp);
}

void	second_pipe_bon(int fd[2], char **argv, char **envp)
{
	int	file;

	close(fd[1]);
	file = open(argv[5], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file == -1)
	{
		perror(argv[5]);
		exit (2);
	}
	if (dup2(fd[0], 0) == -1)
		ft_error(strerror(errno));
	if (dup2(file, 1) == -1)
		ft_error(strerror(errno));
	close(fd[0]);
	close(file);
	define_path(argv[4], envp);
}

void	second_bonus(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		ft_error(strerror(errno));
	pid1 = fork();
	if (pid1 < 0)
		ft_error(strerror(errno));
	if (pid1 == 0)
		first_pipe_bon(fd, argv, envp);
	waitpid(pid1, NULL, 0);
	pid2 = fork();
	if (pid2 < 0)
		ft_error(strerror(errno));
	if (pid2 == 0)
		second_pipe_bon(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, NULL, 0);
	exit(EXIT_SUCCESS);
}
