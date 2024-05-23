/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:04:21 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/23 19:29:39 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	read_heredoc(char *eof, int fds[2])
{
	char	*line;
	int		len;
	
	close(fds[0]);
	while (1)
	{
		line = ft_readline(HEREDOC);
		len = ft_strlen(line);
		if (!len)
			len = 1;
		if (!ft_strncmp(line, eof, len))
		{
			free(line);
			return (1);
		}
		write (fds[1], line, ft_strlen(line));
		free(line);
	}
	return (1);
}

int	ft_heredoc(char *eof)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		read_heredoc(eof, fds);
	else if (pid)
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		wait(NULL);
	}
	return (1);
}
