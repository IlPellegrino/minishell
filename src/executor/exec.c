/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:52:14 by nromito           #+#    #+#             */
/*   Updated: 2024/05/22 15:28:57 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	executor(t_shell *shell)
{
	t_table table;
	int		i;
	int		cmd_len;

	i = -1;
	while (++i < shell->len)
	{
		table = shell->cmd_table[i];
		cmd_len = ft_strlen(table.command);
		if (!(ft_strncmp(table.command, "echo", cmd_len)))
			ft_echo(table.cmd->cmd_arg);
		// else if (!(ft_strncmp(table.command, "cd", cmd_len)))
		// 	ft_cd(table.cmd->cmd_arg);
	}
	return (1);
}