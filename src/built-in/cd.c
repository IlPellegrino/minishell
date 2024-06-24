/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:42:12 by nromito           #+#    #+#             */
/*   Updated: 2024/06/24 18:09:09 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	update_cwd(t_shell *shell, char *to_update)
{
	char	**oldpwd;
	char	*cwd;

	oldpwd = ft_calloc(sizeof(char *), 3);
	oldpwd[0] = ft_strdup("export");
	cwd = getcwd(NULL, 0);
	oldpwd[1] = ft_strjoin(to_update, cwd);
	free(cwd);
	ft_export(oldpwd, shell);
	free_matrix(oldpwd);
}

int	change_dir(char *cd_arg, DIR *folder, t_shell *shell)
{
	DIR		*dest;	

	update_cwd(shell, "OLDPWD=");
	dest = opendir(cd_arg);
	if (dest)
	{
		closedir(folder);
		closedir(dest);
		chdir(cd_arg);
		update_cwd(shell, "PWD=");
		return (1);
	}
	return (0);
}

char	*to_move(char **cd_mat, t_shell *shell)
{
	char	*move;

	if (!cd_mat[1] || !ft_strncmp(cd_mat[1], "~", ft_strlen(cd_mat[1])))
	{
		move = ft_getenv("HOME", shell);
		if (!move)
			return (ft_error(shell, CD_UNSET, "HOME"), NULL);
	}
	else if (!ft_strncmp(cd_mat[1], "-", 2))
	{
		move = ft_getenv("OLDPWD", shell);
		if (!move)
			return (ft_error(shell, CD_UNSET, "OLDPWD"), NULL);
	}
	else
		move = ft_strdup(cd_mat[1]);
	return (move);
}

int	ft_cd(char **cd_mat, t_shell *shell)
{
	DIR				*folder;
	char			*move;

	move = to_move(cd_mat, shell);
	if (!move)
		return (0);
	if (matrix_len(cd_mat) < 3)
	{
		collect_garbage(shell, move, 0);
		folder = opendir(".");
		if (!folder)
			return (perror("minishell"), 0);
		while (readdir(folder))
			if (change_dir(move, folder, shell))
				return (shell->error = 0, 1);
		closedir(folder);
		return (ft_error(shell, CD_DIR, move));
	}
	free (move);
	return (ft_error(shell, CD_ARGS, 0), 0);
}
