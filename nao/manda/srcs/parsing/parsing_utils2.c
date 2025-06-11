/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:00:34 by naorakot          #+#    #+#             */
/*   Updated: 2025/06/11 21:00:38 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libparsing.h"

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
