/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:59:18 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/14 17:40:14 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	delete_heredoc(void)
{
	int		n;
	char	*str;
	char	*heredoc;
	char	*number;

	n = 0;
	str = ft_strdup(".heredoc");
	number = ft_itoa(n++);
	heredoc = ft_strjoin(str, number);
	while (unlink(heredoc) != -1)
	{
		free(number);
		free(heredoc);
		number = ft_itoa(n++);
		heredoc = ft_strjoin(str, number);
	}
	free(number);
	free(str);
	free(heredoc);
	return (1);
}

int	pipe_handler(t_shell *shell, int i, int pid)
{
	t_exec	*exec;

	if (shell->len == 1)
		return (0);
	exec = shell->executor;
	if (shell->len > 1 && !pid)
	{
		close(exec->fds[0]);
		dup2(exec->fds[1], STDOUT_FILENO);
		close(exec->fds[1]);
	}
	else if (shell->len > 1 && pid)
	{
		close(exec->fds[1]);
		dup2(exec->fds[0], STDIN_FILENO);
		close(exec->fds[0]);
	}
	if (i + 1 == shell->len)
	{
		dup2(exec->saved_out, 1);
		close(exec->saved_out);
	}
	return (1);
}

int	perform_redir(t_shell *shell, int i)
{
	t_table	table;

	table = shell->cmd_table[i];
	i = -1;
	if (!table.redirs || !table.command)
		return (0);
	while (table.redirs[++i])
	{
		if (!ft_strncmp(table.redirs[i], "<<", 2)
			|| !ft_strncmp(table.redirs[i], "<", 1))
		{
			dup2(table.fd[i], STDIN_FILENO);
			close(table.fd[i]);
		}
		else if (!ft_strncmp(table.redirs[i], ">", 1)
			|| !ft_strncmp(table.redirs[i], ">>", 2))
		{
			dup2(table.fd[i], STDOUT_FILENO);
			close(table.fd[i]);
		}
	}
	return (1);
}

int	is_builtin(char *str)
{
	int		cmd_len;

	if (!str)
		return (0);
	cmd_len = ft_strlen(str);
	if (!(ft_strncmp(str, "echo", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "cd", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "pwd", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "export", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "unset", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "env", cmd_len)))
		return (1);
	else if (!(ft_strncmp(str, "exit", cmd_len)))
		return (1);
	return (0);
}

void	reset_io(t_exec *exec)
{
	dup2(exec->saved_in, 0);
	close(exec->saved_in);
	dup2(exec->saved_out, 1);
	close(exec->saved_out);
}
