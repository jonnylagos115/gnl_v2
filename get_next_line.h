/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:57:05 by jlagos            #+#    #+#             */
/*   Updated: 2019/03/20 13:10:21 by jlagos           ###   ########.fr       */
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
    int                 fd[1024];
    int                 index;
}                       l_list;
int		get_next_line(const int fd, char **line);

#endif
