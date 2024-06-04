/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:14 by nromito           #+#    #+#             */
/*   Updated: 2024/06/04 11:46:45 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	pipe_handler(t_shell *shell, int i, int pid)
{
	t_table *table;
	t_exec	*exec;

	(void)i;
	table = shell->cmd_table;
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
	}

	return (1);
}

int	perform_redir(t_shell *shell, int i)
{
	t_table	table;
	t_exec	*exec;

	exec = shell->executor;
	table = shell->cmd_table[i];
	i = -1;
	if (!table.redirs)
		return (0);
	while (table.redirs[++i])
	{
		if (!ft_strncmp(table.redirs[i], "<<", 2) || !ft_strncmp(table.redirs[i], "<", 1))
		{		printf("in exec\n");

			dup2(table.fd[i], STDIN_FILENO);
			close(table.fd[i]);
		}
		else if (!ft_strncmp(table.redirs[i], ">", 1) || !ft_strncmp(table.redirs[i], ">>", 2))
		{
			exec->saved_out = dup(STDOUT_FILENO);
			dup2(table.fd[i], STDOUT_FILENO);
			close(table.fd[i]);
		}
	}
	return (1);
}

int	normal_exec(t_table table)
{
	int		cmd_len;
	char	*str;

	str = table.command;
	cmd_len = ft_strlen(str);
	if (!(ft_strncmp(str, "echo", cmd_len)))
		ft_echo(table.cmd->cmd_arg);
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
	return (1);
}


int	fork_exec(t_shell *shell, int i)
{
	t_table	*table;
	t_exec	*exec;

	exec = shell->executor;
	table = shell->cmd_table;
	perform_redir(shell, i);
	if (is_builtin(table->command))
		return (normal_exec(table[i]));
	if (table[i].command)
		if (execve(table[i].cmd->pathname, table[i].cmd->cmd_arg, shell->envp) == -1)
			return (0);
	return (1);
}

int	to_fork(t_shell *shell)
{
	int		i;
	pid_t	pid;
	t_exec	*exec;

	exec = shell->executor;
	i = -1;
	while (++i < shell->len)
	{
		pipe(exec->fds);
		pid = fork();
		if (!pid)
		{
			pipe_handler(shell, i, pid);
			fork_exec(shell, i);
		}
		if (pid)
			pipe_handler(shell, i, pid);
	}
	i = -1;
	while (++i < shell->len)
		wait(0);
	return (1);
}

int	executor(t_shell *shell)
{
	t_table	*table;
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	shell->executor = exec;
	exec->saved_out = dup(1);
	table = shell->cmd_table;
	exec->saved_in = dup(0);
	g_sig_type = 1;
	if (shell->len == 1 && is_builtin(table[0].command))
		normal_exec(table[0]);
	else
	{
		if (!to_fork(shell))
			return (0);
	}
	dup2(exec->saved_in, 0);
	free(exec);
	return (1);
}
