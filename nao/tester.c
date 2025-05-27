#include "libparsing.h"
#include "libmap.h"

int	is_cub(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'b')
		return (0);
	if (str[i - 2] != 'u')
		return (0);
	if (str[i - 3] != 'c')
		return (0);
	if (str[i - 4] != '.')
		return (0);
	return (1);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		printf("%s\n", map[i]);
		free(map[i]);
		i++;
	}
	if (map)
		free(map);
}

void	print_map(t_maps *map)
{
	printf("current map :: player at %d, %d, min %d, %d, max %d, %d\n", map->i, map->j, map->mini, map->minj, map->maxi, map->maxj);
	free_map(map->map);
	free(map);
}


int	main(void)
{
	char	**map;
	t_maps	*mapp;

	t_pars *parse = parsing_pt1_el("texte.cub");
	if (parse)
	{
		map = make_map(parse);
		if (map)
		{
			mapp = get_map(map);
			free_map(map);
			if (mapp)
				print_map(mapp);
		}
		free_parse(parse, NULL);
	}
	return (0);
}
