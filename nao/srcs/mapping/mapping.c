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

t_map	*create_item(t_maps *map, char dir, t_map *prev)
{
	t_map *item;

	if (map->map[map->i][map->j] == '1' || map->map[map->i][map->j] == '?')
		return (NULL);
	item = (t_map *)malloc(sizeof(t_map));
	if (!item)
	{
		map->fail = 1;
		return (NULL);
	}
	item->south = NULL;
	item->east = NULL;
	item->north = NULL;
	item->west = NULL;
	if (dir == 's')
		item->north = prev;
	else if (dir == 'n')
		item->south = prev;
	else if (dir == 'e')
		item->west = prev;
	else if (dir == 'w')
		item->east = prev;
	map->map[map->i][map->j] = '?';
	return (item);
}

t_map	*mapping(t_maps *map, t_map *prev)
{
	t_map *item;
	static int e = 0;

	if (map->fail)
		return (NULL);
	e++;
	printf("it %d :: currently drawing %c from %d, %d, map %c\n", e, map->dir, map->i, map->j, map->map[map->i][map->j]);
	item = create_item(map, map->dir, prev);
	if (!item)
		return (NULL);
	map->dir = 's';
	map->i++;
	if (!item->south)
		item->south = mapping(map, item);
	map->dir = 'n';
	map->i = map->i - 2;
	if (!item->north)
		item->north = mapping(map, item);
	map->dir = 'e';
	map->i++;
	map->j++;
	if (!item->east)
		item->east = mapping(map, item);
	map->dir = 'w';
	map->j = map->j - 2;
	if (!item->west)
		item->west = mapping(map, item);
	map->j++;
	return (item);
}

t_map	*get_map(char **map)
{
	t_map	*player;
	t_maps	mapp;

	get_player(&mapp, map);
	mapp.map = map;
	mapp.dir = 'p';
	mapp.fail = 0;
	player = mapping(&mapp, NULL);
	if (mapp.fail || !player)
	{
		perror("map conversion malloc");
		free_mapp(player);
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
