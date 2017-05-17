/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 18:41:21 by esterna           #+#    #+#             */
/*   Updated: 2017/05/16 17:30:39 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

void	ft_memdel(void **ap)
{
	free(*ap);
	*ap = NULL;
}

void		ft_bzero(void *src, size_t n)
{
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = src;
	while (i < n)
	{
		tmp[i] = 0;
		i++;
	}
}

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	while (i <= size)
	{
		tmp[i] = '\0';
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char *cpydst;

	cpydst = dest;
	while (*src != 0)
		*cpydst++ = *src++;
	*cpydst = *src;
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len;
	char	*ns;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	ns = ft_strnew(len);
	if (!ns)
		return (NULL);
	while (*s1)
	{
		ns[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		ns[i] = *s2;
		s2++;
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

void		array_setup(char **line, char *buf, char *overflow)
{
	ft_memdel((void **)line);
	ft_bzero((void *)buf, sizeof(char) * ft_strlen(buf));
	ft_bzero((void *)overflow, sizeof(char) * ft_strlen(overflow));
	buf[BUFF_SIZE] = '\0';
}

int			check_buf(char *buf)
{
	int i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (i == BUFF_SIZE)
		return (0);
	else if (i == 0 && buf[i] == '\n')
		return (-1);
	return (i);
}

int			read_loop(int fd, int *rd, char *buf, char **overflow)
{
	int n;

	while (!(n = check_buf(buf)) && *rd != 0)
	{
		*rd = read(fd, buf, BUFF_SIZE);
		if (!check_buf(buf))
		{
			*overflow = ft_strjoin(*overflow, buf);
			ft_bzero((void *)buf, sizeof(char) * ft_strlen(buf));
		}
	}
	return (n);
}

void		fill_line(char **line, char **buf, char **overflow, int n)
{
	*line = (char *)malloc(sizeof(char)
			* (ft_strlen(*overflow) + ((n >= 0) ? n : 0) + 1));
	*line = ft_strcpy(*line, *overflow);
	if (n != -1)
		*line = ft_strjoin(*line, *buf);
	(*line)[ft_strlen(*overflow) + ((n >= 0) ? n : 0)] = '\0';
	ft_memdel((void **)buf);
	ft_memdel((void **)overflow);
}

int			get_next_line(const int fd, char **line)
{
	static int		location;
	int				n;
	int				rd[1];
	char			*buf;
	char			*overflow;

	*rd = 1;
	buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	overflow = (char *)malloc(sizeof(char) * 0);
	array_setup(line, buf, overflow);
	if (buf == NULL || overflow == NULL)
		return (0);
	n = read_loop(fd, rd, buf, &overflow);
	if ((n == -1 && !*overflow) || (*rd == 0 && !ft_strlen(buf)))
	{
		*line = (char *)malloc(sizeof(char) * 1);
		(*line)[0] = '\0';
		ft_memdel((void **)&buf);
		ft_memdel((void **)&overflow);
		location = lseek(fd, location + 1, SEEK_SET);
		return (*rd == 0 ? 0 : 1);
	}
	fill_line(line, &buf, &overflow, n);
	location = lseek(fd, location + ft_strlen(*line) + 1, SEEK_SET);
	return ((*rd == 0 || *line == NULL) ? 0 : 1);
}
