#include "libparsing.h"

static int	get_num(int fd, int i)
{
	char	a;
	int		res;

	a = reader(fd);
	if (i == 1)
	{
		while (a && (a == ' ' || a == '\t'))
			a = reader(fd);
	}
	if (a > '9' || a < '0')
		return (-1);
	res = 0;
	while (a >= '0' && a <= '9')
	{
		res = res * 10 + a - '0';
		if (res > 255)
			return (-1);
		a = reader(fd);
	}
	if (i < 3 && a != ',')
		return (-1);
	return (res);
}

char	*get_color(char c, int fd, t_pars *parse)
{
	int	*s;
	int	i;

	if (c == 'F' && !parse->floor[0])
		s = &(parse->floor[0]);
	else if (c == 'C' && !parse->ceiling[0])
		s = &(parse->ceiling[0]);
	else
		return ("invalid element name");
	s[0] = 1;
	i = 1;
	while (i < 4)
	{
		s[i] = get_num(fd, i);
		if (s[i] == -1)
			return ("invalid color input");
		i++;
	}
	return (NULL);
}
