/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:14:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/14 17:00:59 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <sys/stat.h>
#include <dirent.h>

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
	return (1);
}

int	validate_cmd(t_shell *shell, t_table *table)
{
	int		i;
	int		last;
	char	*pathname;

	i = -1;
	last = 0;
	while (++i < shell->len)
	{
		pathname = table[i].cmd->pathname;
		if (pathname)
			last = ft_strlen(pathname) - 1;
		if ((!pathname || pathname[last] == '/')
			&& !is_builtin(table[i].command))
			if (!check_valid(shell, table[i].command))
				return (0);
	}
	return (1);
}
