/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimayumi <mimayumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:19:59 by mimayumi          #+#    #+#             */
/*   Updated: 2025/01/07 20:57:00 by mimayumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_buffer(int fd, char *left_chars, char *buffer);
static char	*set_line(char *line);
static char	*ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	static char	*left_chars;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_chars);
		free(buffer);
		left_chars = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = get_buffer(fd, left_chars, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left_chars = set_line(line);
	return (line);
}

static char	*set_line(char *line_buffer)
{
	char	*left_chars;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	left_chars = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - 1);
	if (*left_chars == 0)
	{
		free(left_chars);
		left_chars = NULL;
	}
	line_buffer[i + 1] = 0;
	return (left_chars);
}

static char	*get_buffer(int fd, char *left_chars, char *buffer)
{
	ssize_t	be_read;
	char	*tmp;

	be_read = 1;
	while (be_read > 0)
	{
		be_read = read(fd, buffer, BUFFER_SIZE);
		if (be_read == -1)
		{
			free(left_chars);
			return (NULL);
		}
		else if (be_read == 0)
			break ;
		buffer[be_read] = 0;
		if (!left_chars)
			left_chars = ft_strdup("");
		tmp = left_chars;
		left_chars = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_chars);
}

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

//#include <stdio.h>

// int main()
// {
// 	 char *line;
// 	 int fd;
// 	 int i = 1;
// 	 printf("BUFFER_SIZE:%d\n", BUFFER_SIZE);
// 	 printf("\nFIRST TEST\n");
// 	 fd = open("mensagem.txt", O_RDONLY);
// 	 while ((line = get_next_line(fd)) != NULL)
// 	 {
// 	 	printf("call %d is:%s", i, line);
// 	 	free(line);
// 	 	i++;
// 	 }
// 	 printf("\nfinal call %d is:%s\n", i, line);
// 	 close (fd);
// 	 printf("\nSECOND TEST (with empty lines)\n");
// 	 i = 1;
// 	 fd = open("mensagem.txt", O_RDONLY);
// 	 while ((line = get_next_line(fd)) != NULL)
// 	 {
// 	 	if (ft_strchr(line, '\n') == 0)
// 	 		printf("call %d is:%s\n", i, line);
// 	 	else
// 	 		printf("call %d is:%s", i, line);
// 	 	free(line);
// 	 	i++;
// 	 }
// 	 printf("final call %d is:%s\n", i, line);
// 	 close(fd);
// 	 printf("\nTHIRD TEST\n");
// 	 printf("negative fd:%s\n", get_next_line(-1));
// 	 printf("\nFOURTH TEST\n");
// 	 fd = open("mensagem.txt", O_RDONLY);
// 	 close(fd);
// 	 printf("close fd (invalid):%s\n", get_next_line(fd));
// }