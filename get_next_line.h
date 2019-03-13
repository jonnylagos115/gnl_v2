/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:57:05 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/15 15:41:32 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 500

# include "./libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct line_list
{
    char                *saved_bytes;
    char                *free_bytes;
    int                 fd;
    struct line_list    *next;
}                       l_list;
int		get_next_line(const int fd, char **line);

#endif
