/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:54:36 by nromito           #+#    #+#             */
/*   Updated: 2024/05/10 11:41:05 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_matrix(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
}

int	get_path(t_shell *shell)
{
	char 	*path;
	char	*temp;
	int		i = -1;

	path = getenv("PATH");
	shell->path_env = ft_split(path, ':');
	if (!shell->path_env)
		return (0);
	collect_garbage(shell, 0, shell->path_env);
	temp = shell->path_env[0];
	shell->path_env[0] = ft_strtrim(temp, "PATH="); // crea la path da passare all'access
	free(temp);
	while (shell->path_env[++i])
	{
		temp = ft_strdup(shell->path_env[i]);
		shell->path_env[i] = ft_strjoin(temp, "/");  // add "/" for access function
		free(temp);
	}
	return (1);
}



int	parsing(t_shell *shell)
{
	//if (!find_pipe(shell))
	//	return (0);
	if (!tokenizer(shell))
		return (0);
	return (1);
}
