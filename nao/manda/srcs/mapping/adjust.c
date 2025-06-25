#include "libparsing.h"

static char	*adjust_line(char *line, int size)
{
	int		i;
	char	*nline;

	i = 0;
	while (line[i])
		i++;
	if (i == size)
		return (line);
	nline = malloc(size + 1);
	if (!nline)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n' && i < size)
	{
		nline[i] = line[i];
		i++;
	}
	while (i < size)
	{
		nline[i] = ' ';
		i++;
	}
	nline[i] = '\0';
	free(line);
	return (nline);
}

static int	map_ll(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

char	**adjust_map(char **map)
{
	int		i;
	char	*line;
	int		max;

	i = 0;
	max = map_ll(map);
	if (!max)
	{
		free_map(map);
		printf("Error\nempty map\n");
		return (NULL);
	}
	while (map[i])
	{
		line = adjust_line(map[i], max);
		if (!line)
		{
			free_map(map);
			printf("Error\nmalloc, adjusting line length\n");
			return (NULL);
		}
		map[i] = line;
		i++;
	}
	return (map);
}
