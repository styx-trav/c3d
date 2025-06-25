#ifndef LIBMAP_H
# define LIBMAP_H

# include "libparsing.h"

typedef struct s_maps
{
	int		i;
	int		j;
	int		mini;
	int		minj;
	int		maxi;
	int		maxj;
	char	dir;
	char	**map;
}		t_maps;

//from mapping/map_add.c
char	**expand_map(char **map);

//from mapping/mapping.c
t_maps	*get_map(char **map);

//from mapping/mapping_utils.c
void	if_wall(t_maps *map, int i, int j);
int		get_player(t_maps *mapp, char **map);

//from utils.c
size_t	ft_strlen(const char *s);

#endif
