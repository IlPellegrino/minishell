/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:40:51 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/14 17:02:26 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <sys/stat.h>
#include <dirent.h>

int	compare_folder(t_shell *shell, struct dirent *curr, char *str)
{
	int	fd;

	fd = open(curr->d_name, __O_DIRECTORY);
	if (fd == -1 && str[0] != '.')
		return (ft_error(shell, NOT_FOLDER, str), 1);
	else if (str[0] != '.' && fd)
	{
		close(fd);
		return (ft_error(shell, FOLDER, str), 1);
	}
	close(fd);
	return (0);
}

int	is_folder(t_shell *shell, char *str)
{
	DIR				*folder;
	struct dirent	*curr;
	char			*new_str;

	folder = opendir(".");
	if (!folder)
		return (0);
	curr = readdir(folder);
	if (str[0] == '.')
		new_str = ft_strdup(str + 2);
	else
		new_str = ft_strdup(str);
	collect_garbage(shell, new_str, 0);
	while (curr)
	{
		if (!ft_strncmp(new_str, curr->d_name, ft_strlen(new_str) - 1))
		{
			if (!compare_folder(shell, curr, str))
				return (closedir(folder), 0);
			return (closedir(folder), 1);
		}
		curr = readdir(folder);
	}
	closedir(folder);
	return (ft_error(shell, NO_FILE, str), 1);
}

int	no_permission(char *str)
{
	if (access(str, X_OK) == 0)
		return (0);
	return (1);
}
