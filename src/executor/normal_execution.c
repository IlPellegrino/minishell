/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:23:05 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/03 12:15:56 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	forkable_command(t_table table)
{
	if (!table.cmd || !table.cmd->pathname)
		return (0);
	if (!access(table.cmd->pathname, X_OK))
		return (1);
	return (0);
}

void	close_remaining_redirs(t_shell *shell)
{
	int		i;
	t_table	*table;

	table = shell->cmd_table;
	i = -1;
	while (++i < shell->len)
		close_redirs(table[i].fd, matrix_len(table[i].redirs));
}

void	init_saved_std(t_exec *exec)
{
	exec->saved_out = dup(1);
	exec->saved_in = dup(0);
}

int	no_pipe(t_shell *shell)
{
	t_exec	*exec;
	t_table	*table;

	exec = shell->executor;
	table = shell->cmd_table;
	exec->saved_out = dup(1);
	exec->saved_in = dup(0);
	if (!parse_redirs(shell, table[0]) || !validate_cmd(shell, table[0]))
	{
		reset_io(exec);
		close_redirs(table[0].fd, matrix_len(table[0].redirs));
		g_sig_type = 0;
		return (0);
	}
	perform_redir(shell, 0);
	normal_exec(table[0].command, table[0], shell, 0);
	return (1);
}
