/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:42:12 by nromito           #+#    #+#             */
/*   Updated: 2024/06/12 18:45:39 by ciusca           ###   ########.fr       */
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
	{
		move = ft_getenv("HOME", shell);
		if (!move)
			return (0);
	}
	else if (cd_mat[1])
		move = ft_strdup(cd_mat[1]);
	if (matrix_len(cd_mat) < 3)
	{
		collect_garbage(shell, move, 0);
		folder = opendir(".");
		if (!folder)
			return (perror("minishell"), 0);
		while (readdir(folder))
			if (change_dir(move, folder))
				return (shell->error = 0, 1);
		closedir(folder);
		return (ft_error(shell, CD_DIR, move));
	}
	free (move);
	return (ft_error(shell, CD_ARGS, 0), 0);
}
