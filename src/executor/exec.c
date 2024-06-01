/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:14 by nromito           #+#    #+#             */
/*   Updated: 2024/06/01 16:07:00 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"



int	executor(t_shell *shell)
{
	t_table	table;
	int		i;
	int		cmd_len;

	i = -1;
	while (++i < shell->len)
	{
		table = shell->cmd_table[i];
		cmd_len = ft_strlen(table.command);
		if (!(ft_strncmp(table.command, "echo", cmd_len)))
			ft_echo(table.cmd->cmd_arg);
		else if (!(ft_strncmp(table.command, "cd", cmd_len)))
			ft_cd(table.cmd->cmd_arg);
		else if (!(ft_strncmp(table.command, "pwd", cmd_len)))
			ft_pwd();
		else if (!(ft_strncmp(table.command, "export", cmd_len)))
			ft_export(table.cmd->cmd_arg, shell);
		else if (!(ft_strncmp(table.command, "unset", cmd_len)))
			ft_unset(table.cmd->cmd_arg, shell);
		// else if (!(ft_strncmp(table.command, "env", cmd_len)))
		// 	ft_env(table.cmd->cmd_arg, shell);
		else if (!(ft_strncmp(table.command, "exit", cmd_len)))
			ft_exit(table.cmd->cmd_arg, shell);
	}
	return (1);
}
