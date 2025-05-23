#include "libparsing.h"

static char	**get_dir(char c, int fd, t_pars *parse)
{
	char	a;
	char	**res;

	if (!read(fd, &a, 1))
		return (NULL);
	if (c == 'S' && a == 'O')
		res = &(parse->south);
	else if (c == 'N' && a == 'O')
		res = &(parse->north);
	else if (c == 'E' && a == 'A')
		res = &(parse->east);
	else if (c == 'W' && a == 'E')
		res = &(parse->west);
	else
		return (NULL);
	if (*res)
		return (NULL);
	return (res);
}

static char	*get_texture(char c, int fd, t_pars *parse)
{
	char	**s;
	char	buf[8];

	s = get_dir(c, fd, parse);
	if (!s)
		return ("invalid element name");
	while (c == ' ' || c == '\t')
		read(fd, &c, 1);
	while (c != '\n' && c != ' ' && c != '\t')
	{
		*s = add_char(*s, c);
		if (!(*s))
			return ("textures, malloc");
		read(fd, &c, 1);
	}
	return (NULL);
}

static char	*get_element(char c, int fd, t_pars *parse)
{
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (get_texture(c, fd, parse));
	//if (c == 'F' || c == 'C')
		//return (get_color);
	return ("invalid element name");
}

static char	*parse_elements(int fd, t_pars *parse)
{
	int	i;
	char	a;
	char	*err;

	i = 0;
	while (i != 6)
	{
		a = move_to_char(fd);
		if (a == '\0')
			return ("missing elements of parsing");
		err = get_element(a, fd, parse);
		if (err)
			return (err);
		i++;
	}
	return (NULL);
}

t_pars	*parsing_pt1_el(char *file)
{
	t_pars	*parse;
	int	fd;
	char	*err_msg;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (NULL);
	}
	parse = make_parse();
	if (!parse)
		return (NULL);
	err_msg = parse_elements(fd, parse);
	if (err_msg)
		return (free_parse(parse, err_msg, fd));
	return (parse);
}
