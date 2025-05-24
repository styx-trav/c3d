/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:54:33 by naorakot          #+#    #+#             */
/*   Updated: 2024/11/06 19:54:42 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H "get_next_line.h"

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 75
# endif

char	*get_next_line(int fd);
size_t	lenn(char buf[BUFFER_SIZE +1], size_t i);
size_t	len_str(char *str);
#endif
