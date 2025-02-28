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
	char	*joined;
	int		rd;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	rd = 1;
	while ((!keep || !ft_strchr(keep, '\n')) && rd != 0)
	{
		rd = read(fd, temp, BUFFER_SIZE);
		if (rd == -1)
			return (ft_handle_error(temp, keep));
		temp[rd] = '\0';
		if (!keep)
			keep = ft_strdup("");
		joined = ft_strjoin(keep, temp);
		free(keep);
		keep = joined;
	}
	return (free(temp), keep);
}

char	*ft_handle_error(char *temp, char *keep)
{
	free(temp);
	if (keep)
		free(keep);
	return (NULL);
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
		rtn[j] = keep[i + j];
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
