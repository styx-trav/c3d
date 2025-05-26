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
		printf("%s", map[i]);
		free(map[i]);
		i++;
	}
	if (map)
		free(map);
}

void	print_map(t_map *player)
{
	char a = 'a';
	while (a != 'x')
	{
		a = reader(0);
		if (a == 'u')
		{
			if (!player->north)
				printf("hitting wall\n");
			else
				player = player->north;
		}
		else if (a == 'd')
		{
			if (!player->south)
				printf("hitting wall\n");
			else
				player = player->south;
		}
		if (a == 'l')
		{
			if (!player->west)
				printf("hitting wall\n");
			else
				player = player->west;
		}
		if (a == 'r')
		{
			if (!player->east)
				printf("hitting wall\n");
			else
				player = player->east;
		}
	}
}

int main()
{
	char	**map;
	t_map	*mapp;

	t_pars *parse = parsing_pt1_el("texte.cub");
	if (parse)
	{
		map = make_map(parse);
		if (map)
		{
			mapp = get_map(map);
			free_map(map);
			if (mapp)
			{
				print_map(mapp);
				free_mapp(mapp);
			}
		}
		free_parse(parse, NULL);
	}
	return (0);
}
