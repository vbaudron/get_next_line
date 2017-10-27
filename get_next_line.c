/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 10:33:46 by vbaudron          #+#    #+#             */
/*   Updated: 2017/10/19 16:19:14 by vbaudron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_erase(t_gnl **elem, int i)
{
	int j;

	j = 0;
	i++;
	if ((*elem)->save[i] == '\0')
	{
		ft_bzero((*elem)->save, i);
		return (1);
	}
	while ((*elem)->save[i + j] != '\0')
	{
		(*elem)->save[j] = (*elem)->save[i + j];
		j++;
	}
	while ((*elem)->save[j] != '\0')
	{
		(*elem)->save[j] = '\0';
		j++;
	}
	return (1);
}

static int		ft_putline(t_gnl **elem, char **line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((*elem)->save[i] != '\n' && (*elem)->save[i] != '\0')
		i++;
	if ((*line = malloc(sizeof(char) * i + 1)) == NULL)
		return (-1);
	while (j < i)
	{
		(*line)[j] = (*elem)->save[j];
		j++;
	}
	(*line)[j] = '\0';
	return (ft_erase(elem, i));
}

static int		ft_read(int fd, t_gnl **elem, char **line, int nb)
{
	char	*tmp;
	int		stop;

	stop = 0;
	tmp = ft_strnew(BUFF_SIZE);
	while (stop == 0 && (nb = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		(*elem)->save = ft_strjoin_free((*elem)->save, tmp);
		tmp = ft_strnew(BUFF_SIZE);
		if (ft_strrchr((*elem)->save, '\n') != NULL)
			stop = 1;
	}
	free(tmp);
	tmp = NULL;
	if (nb == 0)
		(*elem)->done = 1;
	if (nb < 0)
		return (-1);
	if ((*elem)->save[0] == '\0')
	{
		*line = ft_strnew(1);
		return (0);
	}
	return (ft_putline(elem, line));
}

static	t_gnl	*ft_create_struct(t_gnl **elem, int fd)
{
	if (((*elem) = malloc(sizeof(t_gnl))) == NULL)
		return (NULL);
	if (((*elem)->save = ft_strnew(BUFF_SIZE)) == NULL)
		return (NULL);
	(*elem)->done = 0;
	(*elem)->fd = fd;
	return (*elem);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*elem;
	int				check;

	check = 0;
	if (fd < 0 || BUFF_SIZE < 1)
		return (-1);
	if (elem != NULL && (elem->done == 1 || elem->fd != fd))
	{
		if (elem->fd != fd)
			check = 1;
		free(elem->save);
		free(elem);
		elem = NULL;
		if (check == 1)
			return (get_next_line(fd, line));
		return (0);
	}
	if (elem == NULL)
		if ((elem = ft_create_struct(&elem, fd)) == NULL)
			return (-1);
	if (elem->save[0] != '\0' && ft_strrchr(elem->save, '\n') != NULL)
		return (ft_putline(&elem, line));
	else
		return (ft_read(fd, &elem, line, 1));
	return (1);
}
