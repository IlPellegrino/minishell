/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:14 by nromito           #+#    #+#             */
/*   Updated: 2024/06/11 15:58:40 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	normal_exec(t_table table, t_shell *shell)
{
	int		cmd_len;
	char	*str;
	int		fail;

	fail = 0;
	str = table.command;
	if (!str)
		return (0);
	cmd_len = ft_strlen(str);
	if (!(ft_strncmp(str, "echo", cmd_len)))
		fail = ft_echo(table.cmd->cmd_arg);
	else if (!(ft_strncmp(str, "cd", cmd_len)))
		fail = ft_cd(table.cmd->cmd_arg, shell);
	else if (!(ft_strncmp(str, "pwd", cmd_len)))
		fail = ft_pwd();
	else if (!(ft_strncmp(str, "export", cmd_len)))
		fail = ft_export(table.cmd->cmd_arg, shell);
	else if (!(ft_strncmp(str, "unset", cmd_len)))
		fail = ft_unset(table.cmd->cmd_arg, shell);
	else if (!(ft_strncmp(str, "env", cmd_len)))
		fail = ft_env(table.cmd->cmd_arg, shell);
	else if (!(ft_strncmp(str, "exit", cmd_len)))
		fail = ft_exit(table.cmd->cmd_arg, shell);
	return (fail);
}

int	fork_exec(t_shell *shell, int i)
{
	t_table	*table;
	t_cmd	*cmd;

	table = shell->cmd_table;
	cmd = table[i].cmd;
	if (is_builtin(table[i].command))
	{
		if (!normal_exec(table[i], shell))
			return (0);
	}
	else if (table[i].command)
	{
		if (execve(cmd->pathname, cmd->cmd_arg, shell->envp) == -1)
			return (0);
	}
	return (1);
}

int	manage_fork(pid_t pid, t_shell *shell, int i)
{
	t_exec	*exec;

	exec = shell->executor;
	if (pid < 0)
	{
		perror("fork");
		close_shell(shell);
	}
	if (!pid)
	{
		pipe_handler(shell, i, pid);
		perform_redir(shell, i);
		if (!fork_exec(shell, i))
			shell->error = 2;
		free_cmd_table(shell);
		close_shell(shell);
	}
	else
	{
		pipe_handler(shell, i, pid);
		close(exec->fds[1]);
		if (i > 0)
			close(exec->fds[0]);
	}
	return (1);
}

int	to_fork(t_shell *shell)
{
	int		i;
	pid_t	pid;
	t_exec	*exec;
	int		status;

	exec = shell->executor;
	i = -1;
	while (++i < shell->len)
	{
		pipe(exec->fds);
		pid = fork();
		if (i + 1 == shell->len)
			exec->last_pid = pid;
		manage_fork(pid, shell, i);
	}
	i = -1;
	while (++i < shell->len)
	{
		pid = wait(&status);
		if (pid == exec->last_pid)
			shell->error = WEXITSTATUS(status);
	}
	return (1);
}

int	executor(t_shell *shell)
{
	t_table	*table;
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	shell->error = 0;
	collect_garbage(shell, (char *) exec, 0);
	shell->executor = exec;
	exec->saved_out = dup(1);
	table = shell->cmd_table;
	exec->saved_in = dup(0);
	g_sig_type = 2;
	if (shell->len == 1 && (is_builtin(table[0].command) || !table[0].command))
	{
		perform_redir(shell, 0);
		if (!normal_exec(table[0], shell))
			exec->catch = 0;
	}
	else
		to_fork(shell);
	dup2(exec->saved_in, 0);
	close(exec->saved_in);
	if (g_sig_type == SIG_C)
		shell->error = 130;
	else if (g_sig_type == CORE_DUMPED)
		shell->error = 131;
	return (shell->error == 0);
}
