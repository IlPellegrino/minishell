/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:46:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/28 18:32:06 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*expand_pid(void)
{
	int		fd;
	char	*buffer;
	char	*pid;
	int		i;

	buffer = ft_calloc(sizeof(char *), 21);
	fd = open("/proc/self/stat", O_CREAT, O_RDONLY, 0777);
	if (fd == -1)
		return (perror("minishell"), NULL);
	if (read(fd, buffer, 20) == -1)
		return (free(buffer), NULL);
	i = -1;
	while (buffer[i] && buffer[i] != 32)
		i++;
	pid = ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while (buffer[++i] != ' ' && buffer[i])
		pid[i] = buffer[i];
	free(buffer);
	return (pid);
}
