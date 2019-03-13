/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:56:12 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/21 15:01:37 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static l_list	*fill_saved_bytes(l_list *saved_fd, int fd)
{
	char		*temp;
	char		buf[BUFF_SIZE + 1];
	int			bytes;

	if(!(saved_fd = (l_list *)malloc(sizeof(*saved_fd))))
		return (NULL);
	while ((bytes = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if (!(saved_fd->saved_bytes))
			saved_fd->saved_bytes = ft_strnew(1);
		temp = ft_strjoin(saved_fd->saved_bytes, buf);
		free(saved_fd->saved_bytes);
		saved_fd->saved_bytes = temp;
	}
	if (bytes == -1)
		return (NULL);
	saved_fd->fd = fd;
	return (saved_fd);
}

static char		*fill_line(char **line, char *saved_bytes)
{
	int	i;

	i = 0;
	if (!saved_bytes)
		return (NULL);
	while (saved_bytes[i] != '\n' && saved_bytes[i])
		i++;
	if (*saved_bytes != '\n')
	{
		*line = ft_strnew(i);
		ft_strncpy(*line, saved_bytes, i);
		while (i && *saved_bytes != '\n' && *saved_bytes)
		{
			i--;
			saved_bytes++;
		}
	}
	return (*line);
}

int				get_next_line(const int fd, char **line)
{
	static int	track_fd;
	l_list 		saved_fd;

	if (!line || fd < 0)
		return (-1);
	if (!track_fd || track_fd != fd) 
	{
		if (track_fd)
			saved_fd = *saved_fd.next;
		if (!(fill_saved_bytes(&saved_fd, fd)))
			return (-1);
		track_fd = fd;
	}
	if (*(saved_fd.saved_bytes) == '\n')
	{
		saved_fd.saved_bytes++;
		if (*(saved_fd.saved_bytes) == '\n')
			**line = '\0';
	}
	if (!(fill_line(&*line, saved_fd.saved_bytes)))
		return (0);
	return (1);
}
