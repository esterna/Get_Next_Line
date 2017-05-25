/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:39:58 by esterna           #+#    #+#             */
/*   Updated: 2017/05/24 14:59:08 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int			get_next_line(const int fd, char **line)
{
	int rd;
	char *tmp;
	char buf[BUFF_SIZE + 1];
	static char *overflow;

	rd = 1;
	tmp = NULL;
	ft_bzero(buf, (sizeof(char) * (BUFF_SIZE + 1)));
	if (fd < 0 || BUFF_SIZE < 1 || !line || (read(fd, buf, 0) < 0))
		return (-1);
	while (rd > 0)
	{
		if ((rd = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		if ((tmp = ft_strchr(buf, '\n')) || rd == 0)
		{
			if (tmp)
				*tmp = '\0';
			*line = (!overflow) ? ft_strdup(buf) : ft_strjoin(overflow, buf);
			ft_memdel((void **)&overflow);
			ft_bzero((void *)buf, sizeof(char) * (BUFF_SIZE + 1));
			return ((rd > 0) ? 1 : 0);
		}
		else
		{
			tmp = (!overflow) ? ft_strdup(buf) : ft_strjoin(overflow, buf);
			ft_memdel((void **)&overflow);
			ft_bzero((void *)buf, sizeof(char) * (BUFF_SIZE + 1));
			overflow = tmp;
		}
	}
	return (-1);
}
