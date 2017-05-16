/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 19:02:36 by esterna           #+#    #+#             */
/*   Updated: 2017/05/11 20:48:26 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int			main(int argc, char **argv)
{
	int		fd;
	char	*ptr;

	if (argc != 2)
	{
		ft_putstr("usage:\nget_next_line file\n");
		return (0);
	}
	argv++;
	fd = open(*argv, O_RDONLY);
	while (get_next_line(fd, &ptr) > 0)
	{
		ft_putstr(ptr);
		ft_putchar('\n');
	}
	return (0);
}
