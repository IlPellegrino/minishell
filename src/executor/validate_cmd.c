/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:14:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/20 19:31:40 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_table_redirs(t_shell *shell)
{
	t_table *table;
	int		i;

	table = shell->cmd_table;
	i = -1;
	while (++i < shell->len)
		close_redirs(table[i].fd, matrix_len(table[i].redirs));
}

int	check_valid(t_shell *shell, char *str)
{
	int		last;

	last = ft_strlen(str) -1;
	if (!ft_strchr(str, '/'))
		return (ft_error(shell, COMMAND, str));
	else if (is_folder(shell, str))
		return (0);
	else if (no_permission(str))
		return (ft_error(shell, NO_PERMISSION, str));
	else if (not_binary(shell, str))
		return (0);
	return (1);
}

int	validate_cmd(t_shell *shell, t_table table)
{
	int		i;
	int		last;
	char	*pathname;

	i = -1;
	last = 0;
	if (!table.cmd)
		return (0);
	pathname = table.cmd->pathname;
	if (pathname)
		last = ft_strlen(pathname) - 1;
	if ((!pathname || pathname[last] == '/' || table.command[0] == '.')
		&& !is_builtin(table.command))
	{
		if (!check_valid(shell, table.command))
		{
			close_table_redirs(shell);
			return (0);
		}
	}
	return (1);
}
