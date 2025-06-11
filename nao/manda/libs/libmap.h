/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:01:39 by naorakot          #+#    #+#             */
/*   Updated: 2025/06/11 21:01:40 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//from mapping/mapping.c
t_maps	*get_map(char **map);

#endif
