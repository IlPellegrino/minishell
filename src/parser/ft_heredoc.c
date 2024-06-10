/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:04:21 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/10 17:45:33 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*heredoc_name(t_shell *shell)
{
	static int	n;
	char		*here_name;
	char		*num;

	num = ft_itoa(n);
	if (!num)
		return (0);
	here_name = ft_strjoin(".heredoc", num);
	free(num);
	collect_garbage(shell, here_name, 0);
	n++;
	return (here_name);
}

int	read_heredoc(t_shell *shell, char *eof, int fd, int flag)
{
	char	*line;
	int		len;

	while (1)
	{
		g_sig_type = IN_HEREDOC;
		line = ft_readline(HEREDOC);
		if (!line)
			return (0);
		if (ft_strchr(line, '$') && flag == '0')
		{
			line = expand_heredoc(shell, line);
		}
		collect_garbage(shell, line, 0);
		len = ft_strlen(line);
		if (!len)
			len = 1;
		if (!ft_strncmp(line, eof, len + 1))
			return (1);
		write (fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	return (0);
}

void	reset_stdin(int temp_stdin, int fd)
{
	dup2(temp_stdin, 0);
	close(temp_stdin);
	close(fd);
}

int	ft_heredoc(t_shell *shell, t_token *token, int i)
{
	int		fd;
	int		temp_stdin;
	char	*here_name;

	here_name = heredoc_name(shell);
	fd = open(here_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (0);
	temp_stdin = dup(STDIN_FILENO);
	if (!read_heredoc(shell, token->index[i], fd, token->flag[i]))
	{
		shell->error = 0;
		if (g_sig_type == SIG_C)
			shell->error = 130;
		else
			ft_error(shell, HERE_EOF, 0);
		reset_stdin(temp_stdin, fd);
		return (0);
	}
	close(fd);
	close(temp_stdin);
	fd = open(here_name, O_RDONLY);
	if (fd == -1)
		return (0);
	return (fd);
}
