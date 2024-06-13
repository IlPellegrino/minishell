/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:40:51 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/13 19:36:49 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <sys/stat.h>
#include <dirent.h>

int	is_folder(t_shell *shell, char *str)
{
	DIR				*folder;
	struct dirent	*curr;
	int				fd;

	folder = opendir(".");
	if (!folder)
		return (0);
	curr = readdir(folder);
	while (curr)
	{
		if (!ft_strncmp(str, curr->d_name, ft_strlen(curr->d_name) + 1))
		{
			fd = open(curr->d_name, __O_DIRECTORY);
			if (fd == -1)
				return (ft_error(shell, 0, str));
			else
			{
				close(fd);
				return (free(curr), ft_error(shell, 0, str));
			}
		}
		curr = readdir(folder);
	}
	return (0);
}

int	no_permission(char *str)
{
	return (access(str, X_OK));
}

int not_file(char *str)
{
	return (str[0] != '.');
}


int	not_binary(char *str)
{
	(void)str;
	return (0);
}