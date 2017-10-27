/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 11:20:51 by vbaudron          #+#    #+#             */
/*   Updated: 2017/10/03 10:49:03 by vbaudron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# define BUFF_SIZE 5
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef	struct	s_gnl
{
	int		done;
	int		fd;
	char	*save;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
