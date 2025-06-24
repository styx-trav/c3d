#include "libmap.h"

void	if_wall(t_maps *map, int i, int j)
{
	if (map->mini == -1 || i < map->mini)
		map->mini = i;
	if (map->minj == -1 || j < map->minj)
		map->minj = j;
	if (j > map->maxj)
		map->maxj = j;
	if (i > map->maxi)
		map->maxi = i;
}

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
