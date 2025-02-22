/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:42:29 by gbodur            #+#    #+#             */
/*   Updated: 2025/02/15 03:36:06 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_file(int fd, char *keep)
{
	char	*temp;
	int		rd;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	rd = 1;
	while (!ft_strchr(keep, '\n') && rd != 0)
	{
		rd = read(fd, temp, BUFFER_SIZE);
		if (rd == -1)
			return (free(temp), free(keep), NULL);
		temp[rd] = '\0';
		keep = ft_strjoin(keep, temp);
	}
	return (free(temp), keep);
}

char	*ft_extract_line(char *keep)
{
	char	*line;
	int		i;

	i = 0;
	if (!keep[i])
		return (NULL);
	while (keep[i] != '\0' && keep[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (keep[i] != '\n' && keep[i] != '\0')
	{
		line[i] = keep[i];
		i++;
	}
	if (keep[i] == '\n')
	{
		line[i] = keep[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_delete_read(char *keep)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (keep[i] != '\0' && keep[i] != '\n')
		i++;
	if (!keep[i])
		return (free(keep), NULL);
	rtn = malloc(sizeof(char) * (ft_strlen(keep) - i));
	if (!rtn)
		return (NULL);
	i++;
	while (keep[i + j] != '\0')
	{
		rtn[j] = keep[j + i];
		j++;
	}
	rtn[j] = '\0';
	return (free(keep), rtn);
}

char	*get_next_line(int fd)
{
	static char	*keep;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	keep = ft_read_file(fd, keep);
	if (!keep)
		return (NULL);
	line = ft_extract_line(keep);
	keep = ft_delete_read(keep);
	return (line);
}
