#include "libparsing.h"

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

int main()
{
	char	**map;
	t_pars *parse = parsing_pt1_el("texte.cub");
	if (parse)
	{
		map = make_map(parse);
		if (map)
			free_map(map);
		free_parse(parse, NULL);
	}
	return (0);
}
