#include "pipex.h"

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

char	*ft_strjoin_slash(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	str[i] = '/';
	i++;
	j = -1;
	while (++j < ft_strlen(s2))
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

char	**for_path(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (paths);
}

void	define_path(char *argv_n, char **envp)
{
	char	**paths;
	int		i;
	char	*path;
	char	**ar2;

	ar2 = ft_split(argv_n, ' ');
	execve(ar2[0], ar2, envp);
	paths = for_path(envp);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_slash(paths[i], ar2[0]);
		execve(path, ar2, envp);
		free(path);
		i++;
	}
	for_free(paths);
	write(2, ar2[0], ft_strlen(ar2[0]));
	write(2, ": command not found\n", 20);
	for_free(ar2);
	exit(EXIT_SUCCESS);
}
