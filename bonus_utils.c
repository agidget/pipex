#include "pipex.h"

void	*for_free_int(int **arr, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 4)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

void	first_pipes(int argc, char **argv, int **pipes)
{
	int	file1;
	int	i;

	close(pipes[0][0]);
	file1 = open(argv[1], O_RDONLY, 0644);
	if (file1 == -1)
	{
		perror(argv[1]);
		exit(3);
	}
	i = 0;
	while (++i < argc - 4)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	if (dup2(file1, 0) == -1)
		ft_error(strerror(errno));
	if (dup2(pipes[0][1], 1) == -1)
		ft_error(strerror(errno));
	close(file1);
	close(pipes[0][1]);
}

void	last_pipes(int argc, char **argv, int **pipes)
{
	int	file2;
	int	i;

	close(pipes[argc - 5][1]);
	file2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2 == -1)
	{
		perror(argv[argc - 1]);
		exit(3);
	}
	i = -1;
	while (++i < argc - 5)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	if (dup2(pipes[argc - 5][0], 0) == -1)
		ft_error(strerror(errno));
	if (dup2(file2, 1) == -1)
		ft_error(strerror(errno));
	close(file2);
	close(pipes[argc - 5][0]);
}

void	middle_pipes(int argc, int i, int **pipes)
{
	int	j;

	j = -1;
	while (++j < argc - 4)
	{
		if (j != i - 1)
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
	}
	if (dup2(pipes[i - 1][0], 0) == -1)
		ft_error(strerror(errno));
	if (dup2(pipes[i][1], 1) == -1)
		ft_error(strerror(errno));
	close(pipes[i - 1][0]);
	close(pipes[i][1]);
}

void	which_pipe(int argc, char **argv, int **pipes, int i)
{
	if (i == 0)
		first_pipes(argc, argv, pipes);
	else if (i == argc - 4)
		last_pipes(argc, argv, pipes);
	else
		middle_pipes(argc, i, pipes);
}
