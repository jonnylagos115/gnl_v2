/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:56:12 by jlagos            #+#    #+#             */
/*   Updated: 2019/03/27 18:14:38 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*fill_saved_bytes(t_list *saved_fd, int fd)
{
	char		*temp;
	char		buf[BUFF_SIZE + 1];
	int			bytes;

	while ((bytes = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if (!(saved_fd->saved_bytes))
			saved_fd->saved_bytes = ft_strnew(1);
		temp = ft_strjoin(saved_fd->saved_bytes, buf);
		free(saved_fd->saved_bytes);
		saved_fd->saved_bytes = temp;
		if (ft_find_endl(saved_fd->saved_bytes))
			break ;
	}
	if (bytes == -1)
		return (NULL);
	return (saved_fd);
}

static void		update_saved_bytes(t_list *saved_fd, int i)
{
	char	*temp;
	int		len;

	if (i != 0)
	{
		len = ft_strlen(saved_fd->saved_bytes);
		temp = ft_strsub(saved_fd->saved_bytes, (unsigned int)i, len);
		free(saved_fd->saved_bytes);
		saved_fd->saved_bytes = temp;
	}
}

static int		fill_line(char **line, t_list *fill_bytes)
{
	int		i;

	i = 0;
	if (ft_strcmp(fill_bytes->saved_bytes, "") == 0)
		return (0);
	if (*fill_bytes->saved_bytes == '\n')
	{
		update_saved_bytes(fill_bytes, 1);
		*line = ft_strnew(1);
		return (1);
	}
	while (fill_bytes->saved_bytes[i] != '\n' && fill_bytes->saved_bytes[i])
		i++;
	if (*fill_bytes->saved_bytes != '\n')
	{
		*line = ft_strnew(i);
		ft_strncpy(*line, fill_bytes->saved_bytes, i);
		if (fill_bytes->saved_bytes[i])
			i += 1;
	}
	update_saved_bytes(fill_bytes, i);
	return (1);
}

static void		is_diff_fd(t_list *saved_fd, int fd)
{
	if (saved_fd->fd[saved_fd->index] != fd)
	{
		ft_strdel(&saved_fd->saved_bytes);
		saved_fd->index++;
		saved_fd->fd[saved_fd->index] = fd;
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*saved_fd;

	if (!line || fd < 0)
		return (-1);
	if (!saved_fd)
	{
		if (!(saved_fd = (t_list *)malloc(sizeof(*saved_fd))))
			return (-1);
		saved_fd->index = 0;
		saved_fd->fd[saved_fd->index] = fd;
	}
	is_diff_fd(saved_fd, fd);
	if (!(fill_saved_bytes(saved_fd, fd)))
		return (-1);
	if (!(fill_line(&*line, saved_fd)))
		return (0);
	return (1);
}
