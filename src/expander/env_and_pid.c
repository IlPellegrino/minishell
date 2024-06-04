/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:46:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/31 10:20:10 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_getenv(const char *name, t_shell *shell)
{
	int		i;
	int		be;
	int		pos;
	int		len;
	char	*res;

	i = -1;
	pos = -1;
	len = 0;
	be = 0;
	while (shell->envp[++i])
	{
		if (!ft_strncmp(name, shell->envp[i], ft_strlen(name)))
		{
			while (shell->envp[i][++pos] && shell->envp[i][++pos] != '=')
				be++;
			if (shell->envp[i][pos] != '\0')
				while (shell->envp[i][++pos])
					len++;
			res = ft_calloc(sizeof (char *), len + 1);
			if (!res)
				return (NULL);
			len = -1;
			while (shell->envp[i][++be])
				res[++len] = shell->envp[i][be];
			return (res);
		}
	}
	return (NULL);
}

char	*expand_pid(void)
{
	int		fd;
	char	*buffer;
	char	*pid;
	int		i;

	buffer = ft_calloc(sizeof(char *), 21);
	fd = open("/proc/self/stat", O_RDONLY, 0777);
	if (fd == -1)
		return (perror("minishell"), NULL);
	if (read(fd, buffer, 20) == -1)
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != SPACE)
		i++;
	pid = ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while (buffer[++i] != SPACE && buffer[i])
		pid[i] = buffer[i];
	free(buffer);
	return (pid);
}
