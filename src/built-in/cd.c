/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:42:12 by nromito           #+#    #+#             */
/*   Updated: 2024/06/03 13:05:07 by nromito          ###   ########.fr       */
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
		return (1);
	}
	return (0);
}

int	ft_cd(char **cd_mat, t_shell *shell)
{
	DIR				*folder;
	char			*move;

	if (!cd_mat[1] || !ft_strncmp(cd_mat[1], "~", ft_strlen(cd_mat[1])))
		move = getenv("HOME");
	else if (cd_mat[1])
		move = ft_strdup(cd_mat[1]);
	shell->error = 1;
	if (matrix_len(cd_mat) < 3)
	{
		folder = opendir(".");
		if (!folder)
			return (perror("minishell"), 0);
		while (readdir(folder))
			if (change_dir(move, folder))
				return (free(move), 1);
		free (move);
		closedir(folder);
		return (perror("minishell"), 0);
	}
	free (move);
	return (ft_putstr_fd("minishell: too many arguments\n", 2), 0);
}
