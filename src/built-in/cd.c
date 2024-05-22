/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:42:12 by nromito           #+#    #+#             */
/*   Updated: 2024/05/22 17:36:22 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	change_dir(char *cd_arg, DIR *folder)
{
	DIR	*dest;	

	dest = opendir(cd_arg);
	if (dest)
	{
		closedir(folder);
		closedir(dest);
		chdir(cd_arg);
		return (0);
	}
	return (1);
}

int	ft_cd(char **cd_mat)
{
	DIR				*folder;
	struct dirent	*entry;
	char			*move;

	if (!cd_mat[1] || !ft_strncmp(cd_mat[1], "~", ft_strlen(cd_mat[1])))
		move = getenv("HOME");
	else if (cd_mat[1])
		move = ft_strdup(cd_mat[1]);
	if (matrix_len(cd_mat) < 2)
	{
		folder = opendir(".");
		if (!folder)
			return(perror("minishell"), 1);
		entry = readdir(folder);
		while (entry)
		{
			if (!change_dir(move, folder))
				return (0);
			entry = readdir(folder);
		}
		closedir(folder);
		return(perror("minishell"), 1);
	}
	ft_putstr_fd("minishell: too many arguments\n", 2);
	return(1);
}
