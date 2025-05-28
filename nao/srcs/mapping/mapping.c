#include "libmap.h"

static int	get_player(t_maps *mapp, char **map)
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

static void	size_map(t_maps *map, int i, int j)
{
	if (map->map[i][j] == '!')
		return ;
	if (map->map[i][j] == '1')
	{
		if (map->mini == -1 || i < map->mini)
			map->mini = i;
		if (map->minj == -1 || j < map->minj)
			map->minj = j;
		if (j > map->maxj)
			map->maxj = j;
		if (i > map->maxi)
			map->maxi = i;
		return ;
	}
	map->map[i][j] = '!';
	size_map(map, i +1, j);
	size_map(map, i -1, j);
	size_map(map, i, j +1);
	size_map(map, i, j -1);
}

static char	*inloop(char *map, int min, int max)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(max - min + 2);
	if (!s)
		return (NULL);
	while (map[min + i] != '\n' && min + i <= max)
	{
		s[i] = map[min + i];
		i++;
	}
	while (min + i <= max)
	{
		s[i] = ' ';
		i++;
	}
	s[i] = '\0';
	return (s);
}

static char	**reduce_map(char **map, t_maps *mapp)
{
	char	**nmap;
	int		i;

	nmap = malloc(sizeof(char *) * (mapp->maxi - mapp->mini + 2));
	if (!nmap)
		return (NULL);
	i = 0;
	while (mapp->mini + i <= mapp->maxi)
	{
		nmap[i] = inloop(map[mapp->mini + i], mapp->minj, mapp->maxj);
		if (!nmap[i])
		{
			free_map(nmap);
			return (NULL);
		}
		i++;
	}
	nmap[i] = NULL;
	return (nmap);
}

t_maps	*get_map(char **map)
{
	t_maps	*mapp;

	if (!map)
		return (NULL);
	mapp = (t_maps *)malloc(sizeof(t_maps));
	if (!mapp)
		return (NULL);
	get_player(mapp, map);
	mapp->mini = -1;
	mapp->minj = -1;
	mapp->maxi = -1;
	mapp->maxj = -1;
	mapp->map = map;
	mapp->dir = map[mapp->i][mapp->j];
	size_map(mapp, mapp->i, mapp->j);
	mapp->map = reduce_map(map, mapp);
	free_map(map);
	if (!mapp->map)
	{
		perror("map conversion malloc");
		free(mapp);
		return (NULL);
	}
	mapp->i = mapp->i - mapp->mini;
	mapp->j = mapp->j - mapp->minj;
	return (mapp);
}
