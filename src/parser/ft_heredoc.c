/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:04:21 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/28 17:45:53 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	read_heredoc(t_shell *shell, char *eof, int fd, int flag)
{
	char	*line;
	int		len;

	(void)shell;
	while (1)
	{
		g_sig_type = IN_HEREDOC;
		line = ft_readline(HEREDOC);
		if (!line)
			return (0);
		if (ft_strchr(line, '$') && flag == '0')
		{
			line = expand_heredoc(line);
		}
		collect_garbage(shell, line, 0);
		len = ft_strlen(line);
		if (!len)
			len = 1;
		if (!ft_strncmp(line, eof, len))
			return (1);
		write (fd, line, ft_strlen(line));
	}
	return (0);
}

int	ft_heredoc(t_shell *shell, char *eof, int flag)
{
	int	fd;
	int	temp_stdin;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return (0);
	temp_stdin = dup(STDIN_FILENO);
	dup2(STDIN_FILENO, temp_stdin);
	if (!read_heredoc(shell, eof, fd, flag))
	{
		if (g_sig_type == SIG_C)
			shell->error = 130;
		else
		{
			shell->error = 0;
			ft_error(shell, HERE_EOF, 0);
		}
		dup2(temp_stdin, 0);
		close(fd);
		return (0);
	}
	return (1);
}
