#include "pipex.h"

static size_t	q_lines(char *s, char c)
{
	size_t	i;
	size_t	qnt;

	i = 0;
	qnt = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			qnt++;
		while (s[i] != c && s[i])
			i++;
	}
	return (qnt);
}

void	*for_free(char **new)
{
	size_t	i;

	i = 0;
	while (new[i])
	{
		free(new[i]);
		i++;
	}
	free(new);
	return (NULL);
}

static size_t	l_len(char const *s, char c, size_t i)
{
	size_t	len;

	len = 0;
	while (s[i + len] != c && s[i + len])
		len++;
	return (len);
}

static char	**new_modif(char **new, char const *s, char c, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		new[j] = malloc(sizeof(char) * (l_len(s, c, i) + 1));
		if (!new[j])
			for_free(new);
		k = -1;
		while (++k < l_len(s, c, i))
			new[j][k] = s[i + k];
		new[j][k] = '\0';
		j++;
		while (s[i] != c && s[i])
			i++;
	}
	new[j] = 0;
	return (new);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**new;

	if (!s)
		return (NULL);
	new = malloc(sizeof(char *) * (q_lines((char *)s, c) + 1));
	if (!new)
		return (NULL);
	if (q_lines((char *)s, c) == 0)
	{
		new[0] = 0;
		return (new);
	}
	i = 0;
	new = new_modif(new, s, c, i);
	return (new);
}
