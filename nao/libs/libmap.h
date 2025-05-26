#ifndef LIBMAP_H
# define LIBMAP_H

# include "libparsing.h"

typedef struct s_map
{
	struct s_map	*north;
	struct s_map	*south;
	struct s_map	*east;
	struct s_map	*west;
	//here access to the colors and texture (maybe in a separate structure ?)
}			t_map;

typedef struct s_maps
{
	int	i;
	int	j;
	char	dir;
	char	**map;
	int	fail;
}		t_maps;

t_map	*get_map(char **map);
t_map	*mapping(t_maps *map, t_map *prev);
void	free_mapp(t_map *mapp);

#endif
