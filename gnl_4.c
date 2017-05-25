/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:30:19 by esterna           #+#    #+#             */
/*   Updated: 2017/05/24 19:31:16 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int			get_next_line(const int fd, char **line)
{
	int				n;
	int				rd;
	char			*tmp;
	static char		*overflow[MAX_FD];
	char			buf[BUFF_SIZE + 1];

	ft_bzero(buf, BUFF_SIZE + 1);
	if (fd < 0 || BUFF_SIZE < 1 || !line || (read(fd, buf, 0) < 0))
		return (-1);
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!(overflow[fd]))
			overflow[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(overflow[fd], buf);
			ft_memdel((void **)&overflow[fd]);
			overflow[fd] = tmp;
		}
		ft_bzero(buf, BUFF_SIZE);
		if ((tmp = ft_strchr(overflow[fd], '\n')))
			break ;
	}
	if (rd == 0 && !overflow[fd])
	{
		ft_strclr(*line);
		return (0);
	}
	if (overflow[fd] && !(tmp = ft_strchr(overflow[fd], '\n')) && rd == 0)
	{
		*line = ft_strdup(overflow[fd]);
		ft_memdel((void **)&overflow[fd]);
		return (0);
	}
	n = ((tmp - overflow[fd]) > 0 ? (tmp - overflow[fd]) + 1 : 1);
	*line = ft_strsub(overflow[fd], 0, (n > 1) ? n - 1 : n);
	tmp = ft_strsub(overflow[fd], n, ft_strlen(overflow[fd] + n));
	ft_memdel((void **)&overflow[fd]);
	overflow[fd] = tmp;
	return (1);
}
