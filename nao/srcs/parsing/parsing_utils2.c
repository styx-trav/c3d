#include "libparsing.h"

/*printf("south texture :: %s\n", parse->south);
printf("east texture :: %s\n", parse->east);
printf("west texture :: %s\n", parse->west);
printf("north texture :: %s\n", parse->north);
if (parse->floor[0])
printf("floor color : %d.%d.%d\n", parse->floor[1], parse->floor[2], parse->floor[3]);
if (parse->ceiling[0])
printf("ceiling color : %d.%d.%d\n", parse->ceiling[1], parse->ceiling[2], parse->ceiling[3]);
*/

t_pars	*free_parse(t_pars *parse, char *err_msg)
{
	if (parse->fd != -1)
		close(parse->fd);
	if (err_msg)
	{
		write(2, "Error\n", 6);
		printf("%s\n", err_msg);
	}
	if (parse->south)
		free(parse->south);
	if (parse->east)
		free(parse->east);
	if (parse->west)
		free(parse->west);
	if (parse->north)
		free(parse->north);
	free(parse);
	return (NULL);
}

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
