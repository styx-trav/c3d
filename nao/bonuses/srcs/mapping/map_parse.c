/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltantin <ltantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:20:34 by ltantin           #+#    #+#             */
/*   Updated: 2025/06/26 16:20:35 by ltantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparsing.h"

static char	**add_to_map(char **map, char *line)
{
	int		i;
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

static int	at_wall(char **map, int i, int j)
{
	int	res;

	res = 0;
	if (map[i][j] == '\n' && map[i][j +1] == '\n')
	{
		printf("Error\nempty line in map\n");
		return (1);
	}
	if (i == 0 || j == 0)
		res = 1;
	else if (!map[i + 1] || !map[i][j + 1] || map[i][j + 1] == '\n')
		res = 1;
	else if (map[i -1][j] == ' ' || map[i +1][j] == ' '
		|| map[i][j -1] == ' ' || map[i][j +1] == ' ')
		res = 1;
	if (res)
		printf("Error\nmissing wall at map edge\n");
	return (res);
}

static int	check_map(char **map, int i, int j, int player)
{
	char	a;

	a = map[i][j];
	if (a == '2' && check_door(map, i, j))
		return (-1);
	if (!instr("120NWESM \n", a))
	{
		printf("forbidden character in map\n");
		return (-1);
	}
	if (instr("NWES", a))
		player++;
	if (player > 1)
	{
		printf("Error\nmultiple players\n");
		return (-1);
	}
	if (!instr("\n 1", a) && at_wall(map, i, j))
		return (-1);
	return (player);
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
			player = check_map(map, i, j, player);
			if (player == -1)
				return (0);
			j++;
		}
		i++;
	}
	if (!player)
		printf("Error\nno player\n");
	return (player);
}

char	**make_map(t_pars *parse)
{
	char	**map;
	char	*line;

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
	map = adjust_map(map);
	if (!map)
		return (NULL);
	map = map_errors(reader(parse->fd), map);
	return (map);
}
