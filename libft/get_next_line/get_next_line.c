/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:50:04 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/23 19:14:57 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*free_all(char *buffer, char *file)
{
	free(buffer);
	free(file);
	file = NULL;
	return (NULL);
}

char	*trim_first_line(char *str)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (str[i] == '\n')
		i++;
	len = ft_strlen(str);
	len -= i;
	temp = str;
	str = ft_substr(temp, i, len + 1);
	free(temp);
	return (str);
}

char	*get_curr_line(const char *str)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (str[i] == '\n')
		i++;
	dup = ft_calloc(i + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (str && str[i] != 0 && str[i] != '\n')
	{
		dup[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		dup[i] = '\n';
		dup[i + 1] = 0;
	}
	else
		dup[i] = 0;
	return (dup);
}

char	*find_line(char *file, int fd)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	if (!file)
		file = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!file)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (!(ft_strchr(buffer, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_all(buffer, file));
		buffer[bytes_read] = 0;
		temp = file;
		file = ft_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	return (file);
}

char	*get_next_line(int fd)
{
	static char	*file[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	file[fd] = find_line(file[fd], fd);
	if (!file[fd])
		return (NULL);
	line = get_curr_line(file[fd]);
	file[fd] = trim_first_line(file[fd]);
	if (!*line)
	{
		if (file[fd] != NULL)
			free(file[fd]);
		file[fd] = NULL;
		return (free(line), NULL);
	}
	if (!file[fd])
		free(line);
	if (file[fd][0] == 0)
	{
		free(file[fd]);
		file[fd] = NULL;
	}
	return (line);
}
