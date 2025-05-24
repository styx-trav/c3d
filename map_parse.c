#include "libparsing.h"

char	**add_to_map(char **map, char *line)
{
	int	i;
	char	**nmap;

	i = 0;
	while (map && map[i])
		i++;
	nmap = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (map && map[i])
	{
		if (nmap)
			nmap[i] = map[i];
		else
			free(map[i]);
		i++;
	}
	if (nmap)
	{
		nmap[i] = line;
		nmap[i + 1] = NULL;
	}
	else
		perror("make_map, malloc");
	free(map);
	return (nmap);
}

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

int	check_map(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	if (!map || !map[0])
	{
		printf("no map\n");
		return (0);
	}
	while (map[i])
	{
		j = 0;
		while (map[i][j] && instr("10NWES \n", map[i][j]))
			j++;
		if (map[i][j])
		{
			printf("forbidden character in map\n");
			return (0);
		}
		max = j;
		i++;
	}
	return (max);
}

char	*replace_len(char *liner, int max)
{
	char	*line;
	int	i;

	if (len(liner) == max)
		return (liner);
	line = malloc(max + 1);
	i = 0;
	while (line && liner && liner[i] != '\n')
	{
		line[i] = liner[i];
		i++;
	}
	while (line && i < max - 1)
	{
		line[i] = ' ';
		i++;
	}
	if (line)
	{
		line[i] = '\n';
		line[i +1] = '\0';
	}
	free(liner);
	return (line);
}

int	at_wall(char **map, int i, int j)
{
	int	res;

	res = 0;
	if (i == 0 || j == 0)
		res = 1;
	else if (!map[i + 1] || map[i][j + 1] == '\n')
		res = 1;
	else if (map[i -1][j] == ' ' || map[i +1][j] == ' '
		|| map[i][j -1] == ' ' || map[i][j +1] == ' ')
		res = 1;
	if (res)
		printf("Error\nmissing wall at map edge\n");
	return (res);
}

int	last_map_check(char **map)
{
	int	player;
	int	i;
	int	j;

	player = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (instr("NWES", map[i][j]))
				player++;
			if (player > 1)
			{
				printf("Error\nmultiple players\n");
				return (0);
			}
			if (!instr("\n 1", map[i][j]) && at_wall(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	if (!player)
		printf("Error\nno player\n");
	return (player);
}
				
int	adjust_map(char **map, int max)
{
	int	i;
	char	*line;

	i = 0;
	while (map[i])
	{
		line = replace_len(map[i], max);
		if (!line)
		{
			perror("adjust_map, malloc");
			return (0);
		}
		map[i] = line;
		i++;
	}
	i = last_map_check(map);
	return (i);
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

char	**make_map(t_pars *parse)
{
	char	**map;
	char	*line;
	int	max_len;

	map = NULL;
	line = get_next_line(parse->fd);
	while (line && is_empty(line))
	{
		free(line);
		line = get_next_line(parse->fd);
	}
	while (line)
	{
		map = add_to_map(map, line);
		if (!map)
			return (NULL);
		line = get_next_line(parse->fd);
	}
	if (reader(parse->fd))
	{
		printf("gnl, malloc");
		free_map(map);
		return (NULL);
	}
	max_len = check_map(map);
	if (!max_len || !adjust_map(map, max_len))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
