/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:14:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/13 19:43:50 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <sys/stat.h>
#include <dirent.h>

int	check_valid(t_shell *shell, char *str)
{
	int	last;

	last = ft_strlen(str) -1;
	printf("str = %s\n", str);
	if (!ft_strchr(str, '/'))
	{
		return (ft_error(shell, COMMAND, str));
	}
	else if (is_folder(shell, str) && str[last] == '/' && str[0] != '.')
		return (ft_error(shell, -1, str));
	else if (not_file(str))
		return (ft_error(shell, -1, str));
	else if (no_permission(str))
		return (ft_error(shell, SYNTAX, str));
	//else if (not_binary(str))
	//	return (ft_error(shell, 0, str));
	return (1);
}

int	validate_cmd(t_shell *shell, t_table *table)
{
	int	i;
	int	is_cmd;

	is_cmd = 0;
	i = -1;
	while (++i < shell->len)
	{
		if (!get_pathname(shell, table[i].command))
			is_cmd = 1;
		printf("is cmd = %d\n", is_cmd);
		if (!check_valid(shell, table[i].command) && !is_cmd)
			return (0);
		is_cmd = 0;
	}
	return (shell->error == 0);
}
