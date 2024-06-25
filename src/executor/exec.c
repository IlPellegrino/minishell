/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:14 by nromito           #+#    #+#             */
/*   Updated: 2024/06/25 16:49:55 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	normal_exec(char *str, t_table table, t_shell *shell, pid_t pid)
{
	int		cmd_len;
	int		fail;

	fail = 0;
	if (!str)
		return (0);
	cmd_len = ft_strlen(str);
	if (!(ft_strncmp(str, "echo", cmd_len + 1)))
		fail = ft_echo(table.cmd->cmd_arg);
	else if (!(ft_strncmp(str, "cd", cmd_len + 1)))
		fail = ft_cd(table.cmd->cmd_arg, shell);
	else if (!(ft_strncmp(str, "pwd", cmd_len + 1)))
		fail = ft_pwd();
	else if (!(ft_strncmp(str, "export", cmd_len + 1)))
		fail = ft_export(table.cmd->cmd_arg, shell);
	else if (!(ft_strncmp(str, "unset", cmd_len + 1)))
		fail = ft_unset(table.cmd->cmd_arg, shell);
	else if (!(ft_strncmp(str, "env", cmd_len + 1)))
		fail = ft_env(table.cmd->cmd_arg, shell);
	else if (!(ft_strncmp(str, "exit", cmd_len + 1)))
		fail = ft_exit(table.cmd->cmd_arg, shell, pid);
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
		if (!normal_exec(table[i].command, table[i], shell, 1))
			return (0);
	}
	else if (table[i].command)
	{
		if (execve(cmd->pathname, cmd->cmd_arg, shell->envp) == -1)
		{
			perror("minishell");
			return (0);
		}
	}
	return (1);
}

int	manage_fork(pid_t pid, t_shell *shell, int i)
{
	t_exec	*exec;

	exec = shell->executor;
	if (pid < 0)
		close_shell(shell);
	if (!pid)
	{
		pipe_handler(shell, i, pid);
		if (!parse_redirs(shell, shell->cmd_table[i])
			|| !validate_cmd(shell, shell->cmd_table[i]))
		{
			reset_io(exec);
			close_shell(shell);
		}
		perform_redir(shell, i);
		if (!fork_exec(shell, i))
			shell->error = errno;
		free_cmd_table(shell);
		reset_io(exec);
		close_shell(shell);
	}
	pipe_handler(shell, i, pid);
	if (i > 0)
		close(exec->fds[0]);
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
	init_saved_std(exec);
	while (++i < shell->len)
	{
		if (shell->len > 1)
			pipe(exec->fds);
		pid = fork();
		if (pid < 0)
			perror("minishell");
		if (i + 1 == shell->len)
			exec->last_pid = pid;
		manage_fork(pid, shell, i);
	}
	i = -1;
	while (++i < shell->len)
		if (wait(&status) == exec->last_pid)
			shell->error = WEXITSTATUS(status);
	return (1);
}

int	executor(t_shell *shell)
{
	t_table	*table;
	t_exec	*exec;

	table = shell->cmd_table;
	shell->executor = malloc(sizeof(t_exec));
	if (!shell->executor)
		return (0);
	collect_garbage(shell, (char *) shell->executor, 0);
	shell->error = 0;
	exec = shell->executor;
	g_sig_type = 2;
	if (shell->len == 1 && (is_builtin(table[0].command)
			|| !table[0].command || !forkable_command(table[0])))
	{
		if (!no_pipe(shell))
			return (0);
	}
	else
		to_fork(shell);
	reset_io(exec);
	sig_handle(shell);
	close_remaining_redirs(shell);
	g_sig_type = 0;
	return (shell->error == 0);
}
