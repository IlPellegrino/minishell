/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:42:12 by nromito           #+#    #+#             */
/*   Updated: 2024/05/22 15:58:54 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_cd(char **cd_mat)
{
	DIR				*folder;
	struct dirent	*entry;

	if (cd_mat[1] && !cd_mat[2])
	{
		folder = opendir(".");
		if (!folder)
		{
			perror("minishell");
			return(1);
		}
		while ((entry = readdir(folder)))
		{
			if (!ft_strncmp(cd_mat[1], (char *)folder, ft_strlen(cd_mat[1])))
			{
				closedir(folder);
				chdir(cd_mat[1]);
				return (0);
			}
		}
		closedir(folder);
		perror("minishell");
		return(1);
	}
	else
		return(1);
}
