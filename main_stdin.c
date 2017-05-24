/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 217/5/23 15:19:35 by esterna           #+#    #+#             */
/*   Ufddated: 217/5/23 15:19:35 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int			main()
{
	char *line;
	int fd = 1;

	write(fd, "abcd\n", 5);
	write(fd, "efgh\n", 5);
	write(fd, "ijkl\n", 5);
	write(fd, "mnofd\n", 5);
	write(fd, "qrst\n", 5);
	write(fd, "uvwx\n", 5);
	write(fd, "yzab\n", 5);
	get_next_line(fd, &line);
	printf("%d\n", ft_strcmp(line, "abcd"));
	get_next_line(fd, &line);
	printf("%d\n", ft_strcmp(line, "efgh"));
	get_next_line(fd, &line);
	printf("%d\n", ft_strcmp(line, "ijkl"));
	get_next_line(fd, &line);
	printf("%d\n", ft_strcmp(line, "mnofd"));
	get_next_line(fd, &line);
	printf("%d\n", ft_strcmp(line, "qrst"));
	get_next_line(fd, &line);
	printf("%d\n", ft_strcmp(line, "uvwx"));
	get_next_line(fd, &line);
	printf("%d\n", ft_strcmp(line, "yzab"));

	return (0);
}
