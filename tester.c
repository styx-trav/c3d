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

int main()
{
	t_pars *parse = parsing_pt1("texte.cub");
	if (parse)
		free_parse(parse, NULL, -1);
	return (0);
}
