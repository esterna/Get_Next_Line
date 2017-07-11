/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 19:02:36 by esterna           #+#    #+#             */
/*   Updated: 2017/07/10 19:02:10 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*
int 			main(void)
{
	char 	*line;
	int		out;
	int		p[2];
	char 	*str;
	int		len = 50;

	str = (char *)malloc(1000 * 1000);
	*str = '\0';
	while (len--)
		strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	out = dup(1);
	pipe(p);
	dup2(p[1], 1);

	if (str)
		write(1, str, strlen(str));
	close(p[1]);
	dup2(out, 1);
	get_next_line(p[0], &line);
	if(strcmp(line, str) == 0)
		printf("PASS\n");
	else
	{
		printf("%s\n", line);
		printf("%s\n", str);
	}
	free(str);
	free(line);
	return(0);
}


int			main(int argc, char **argv)
{
	int		fd;
	char	*ptr;

	if (argc != 2)
	{
		printf("usage:\nget_next_line file\n");
		return (0);
	}
	argv++;
	fd = open(*argv, O_RDONLY);
	while (get_next_line(fd, &ptr) > 0)
		printf("%s\n", ptr);
	free(ptr);
	return (0);
}
*/
void			mt_assert(int boul)
{
	if (boul)
		printf("PASS\n");
	else
		printf("FAIL\n");
}

int				main(void)
{/*
char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	char		*filename;
	int			errors;

	filename = "gnl3_2.txt";
	fd = open(filename, O_RDONLY);
	if (fd > 2)
	{
		count_lines = 0;
		errors = 0;
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			if (count_lines == 0 && strcmp(line, "1234567890abcde") != 0)
				errors++;
			if (count_lines == 1 && strcmp(line, "fghijklmnopqrst") != 0)
				errors++;
			count_lines++;
			if (count_lines > 50)
				break ;
		}
		close(fd);
		if (count_lines != 2)
			printf("-> must have returned '1' twice instead of %d time(s)\n", count_lines);
		if (errors > 0)
			printf("-> must have read \"1234567890abcde\" and \"fghijklmnopqrst\"\n");
		if (count_lines == 2 && errors == 0)
			printf("OK\n");
	}
	else
		printf("An error occured while opening file %s\n", filename);

char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	char		*filename;
	int			errors;

	filename = "gnl3_1.txt";
	fd = open(filename, O_RDONLY);
	if (fd > 2)
	{
		count_lines = 0;
		errors = 0;
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			if (count_lines == 0 && strcmp(line, "1234567890abcde") != 0)
				errors++;
			count_lines++;
			if (count_lines > 50)
				break ;
		}
		close(fd);
		if (count_lines != 1)
			printf("-> must have returned '1' once instead of %d time(s)\n", count_lines);
		if (errors > 0)
			printf("-> must have read \"1234567890abcde\" instead of \"%s\"\n", line);
		if (count_lines == 1 && errors == 0)
			printf("OK\n");
	}
	else
		printf("An error occured while opening file %s\n", filename);

	char *line;
	int fd;
	int fd2;
	int fd3;
	int	diff_file_size;

    system("mkdir -p sandbox");
	system("openssl rand -out sandbox/large_file.txt -base64 $((50 * 1000 * 3/4)) 2> /dev/null");

	fd = open("sandbox/large_file.txt", O_RDONLY);
	fd2 = open("sandbox/large_file.txt.mine", O_CREAT | O_RDWR | O_TRUNC, 0755);

	while (get_next_line(fd, &line) == 1)
	{
	    write(fd2, line, strlen(line));
	    write(fd2, "\n", 1);
	}

	close(fd);
	close(fd2);

	system("diff sandbox/large_file.txt sandbox/large_file.txt.mine > sandbox/large_file.diff");
	fd3 = open("sandbox/large_file.diff", O_RDONLY);
	diff_file_size = read(fd3, NULL, 10);
	close(fd3);

	mt_assert(diff_file_size == 0);


	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd\n", 5);
	write(fd, "efgh\n", 5);
	write(fd, "ijkl\n", 5);
	write(fd, "mnop\n", 5);
	write(fd, "qrst\n", 5);
	write(fd, "uvwx\n", 5);
	write(fd, "yzab\n", 5);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcd") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "efgh") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "ijkl") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "mnop") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "qrst") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "uvwx") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "yzab") == 0);
	ret = get_next_line(p[0], &line);
	mt_assert(ret == 0);
*/
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcdefghijklmnop\n", 17);
	write(fd, "qrstuvwxyzabcdef\n", 17);
	write(fd, "ghijklmnopqrstuv\n", 17);
	write(fd, "wxyzabcdefghijkl\n", 17);
	write(fd, "mnopqrstuvwxyzab\n", 17);
	write(fd, "cdefghijklmnopqr\n", 17);
	write(fd, "stuvwxzabcdefghi\n", 17);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "abcdefghijklmnop") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "qrstuvwxyzabcdef") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "ghijklmnopqrstuv") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "wxyzabcdefghijkl") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "mnopqrstuvwxyzab") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "cdefghijklmnopqr") == 0);
	get_next_line(p[0], &line);
	mt_assert(strcmp(line, "stuvwxzabcdefghi") == 0);
	ret = get_next_line(p[0], &line);
	mt_assert(ret == 0);
	return (0);
}
