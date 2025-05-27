#include "libparsing.h"

int	instr(char *str, char a)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == a)
			return (1);
		i++;
	}
	return (0);
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (1);
	return (0);
}

char	**map_errors(char a, char **map)
{
	if (a != '\0')
	{
		printf("gnl, malloc");
		free_map(map);
		return (NULL);
	}
	if (!last_map_check(map))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
