#include "pipex.h"

void	check_args(int argc, char **argv, char **envp)
{
	if (argc < 5)
		ft_error("Input error\n");
	if (argc == 6 && ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])) == 0)
		second_bonus(argv, envp);
}

int	**for_pipes(int argc)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (argc - 4));
	if (!pipes)
		exit(1);
	i = -1;
	while (++i < argc - 4)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			exit(1);
	}
	i = -1;
	while (++i < argc - 4)
	{
		if (pipe(pipes[i]) == -1)
			ft_error(strerror(errno));
	}
	return (pipes);
}

void	for_end(int argc, int **pipes, int *pids)
{
	int	i;

	i = -1;
	while (++i < argc - 4)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	i = -1;
	while (++i < argc - 3)
		waitpid(pids[i], NULL, 0);
	free(pids);
	for_free_int(pipes, argc);
}

int	main(int argc, char **argv, char **envp)
{
	int	*pids;
	int	**pipes;
	int	i;

	check_args(argc, argv, envp);
	pids = malloc(sizeof(int) * (argc - 3));
	if (!pids)
		exit(1);
	pipes = for_pipes(argc);
	i = -1;
	while (++i < argc - 3)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			ft_error(strerror(errno));
		if (pids[i] == 0)
		{
			which_pipe(argc, argv, pipes, i);
			define_path(argv[i + 2], envp);
		}
	}
	for_end(argc, pipes, pids);
}
