#include "libmap.h"

int	get_player(t_maps *mapp, char **map)
{

	mapp->i = 0;
	while (map[mapp->i])
	{
		mapp->j = 0;
		while (map[mapp->i][mapp->j])
		{
			if (instr("NWSE", map[mapp->i][mapp->j]))
				return (1);
			mapp->j++;
		}
		mapp->i++;
	}
	return (0);
}

void	assign_prev(char dir, t_map *s, t_map *prev)
{
	s->north = NULL;
	s->south = NULL;
	s->east = NULL;
	s->west = NULL;
	s->type = 1;
	if (dir == 'n')
		s->south = prev;
	if (dir == 's')
		s->north = prev;
	if (dir == 'w')
		s->east = prev;
	if (dir == 'e')
		s->west = prev;
}

int	distribute(t_maps *map, t_map *s)
{
	if (map->map[map->i][map->j] == '1')
		return (1);
	s->type = 0;
	map->dir = 'n';
	map->i--;
	if (!mapping(map, &(s->north), s))
		return (0);
	map->dir = 's';
	map->i++;
	if (!mapping(map, &(s->south), s))
		return (0);
	map->dir = 'e';
	map->j++;
	if (!mapping(map, &(s->east), s))
		return (0);
	map->dir = 'w';
	map->j--;
	if (!mapping(map, &(s->west), s))
		return (0);
	return (1);
}

int	mapping(t_maps *map, t_map **s, t_map *prev)
{
	char	dir;
	static int e = 0;

	dir = map->dir;
	if (*s)
		return (1);
	printf("drawing %c at %d, %d, map %c\n", dir, map->i, map->j, map->map[map->i][map->j]);
	e++;
	if (e > 13)
		return (0);
	*s = (t_map *)malloc(sizeof(t_map));
	if (!(*s))
		return (0);
	assign_prev(map->dir, *s, prev);
	if (!distribute(map, *s))
		return (0);
	if (dir == 'n')
		map->i++;
	else if (dir == 's')
		map->i--;
	else if (dir == 'e')
		map->j--;
	else if (dir == 'w')
		map->j++;
	return (1);
}

t_map	*get_map(char **map)
{
	t_map	*player;
	t_maps	mapp;

	get_player(&mapp, map);
	mapp.map = map;
	player = NULL;
	mapp.dir = 'p';
	if (!mapping(&mapp, &player, NULL))
	{
		free_mapp(player);
		perror("map conversion malloc");
		return (NULL);
	}
	return (player);
}

void	free_mapp(t_map *mapp)
{
	if (!mapp)
		return ;
	if (mapp->north)
		mapp->north->south = NULL;
	if (mapp->south)
		mapp->south->north = NULL;
	if (mapp->east)
		mapp->east->west = NULL;
	if (mapp->west)
		mapp->west->east = NULL;
	free_mapp(mapp->north);
	free_mapp(mapp->south);
	free_mapp(mapp->east);
	free_mapp(mapp->west);
	free(mapp);
}
