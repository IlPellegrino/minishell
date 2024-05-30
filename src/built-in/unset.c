/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:41:30 by nromito           #+#    #+#             */
/*   Updated: 2024/05/30 10:06:09 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// char	**copy_new_envp(char *envp, int len, char **matrix, char *to_delete)
// {
// 	int	i;
// 	int	len2;

// 	i = -1;
// 	len2 = -1;
// 	while (envp[++len2] && envp[len2] != '=')
// 			;
// 	if (len2 == len)
// 	{
// 		if (ft_strncmp(envp, to_delete, len))
// 		{
// 			matrix[++i] = ft_strdup(envp);
// 			if (!matrix[i])
// 				return (0);
// 		}
// 	}
// 	else
// 	{
// 		matrix[++i] = ft_strdup(envp);
// 		if (!matrix[i])
// 			return (0);
// 	}
// 	return (matrix);
// }

char	**create_matrix(char *to_delete, t_shell *shell)
{
	int		i;
	int		j;
	int		len;
	int		len2;
	char	**matrix;

	i = -1;
	j = -1;
	matrix = ft_calloc(sizeof (char **), matrix_len(shell->envp));
	while (shell->envp[++i])
	{
		len = -1;
		len2 = -1;
		while (to_delete[++len])
		{
			if ((!ft_isalpha(to_delete[len]) && to_delete[len] != US)
				&& ft_isdigit(to_delete[0]))
			{
				printf("minishell: unset: `%s': not a valid identifier\n", to_delete);
				return (0);
			}
		}
		// matrix = copy_new_envp(shell->envp[i], len, matrix, to_delete);
		// if (!matrix)
		// 	return (0);
		while (shell->envp[i][++len2] && shell->envp[i][len2] != '=')
			;
		if (len2 == len)
		{
			if (ft_strncmp(shell->envp[i], to_delete, len))
			{
				matrix[++j] = ft_strdup(shell->envp[i]);
				if (!matrix[j])
					return (0);
			}
		}
		else
		{
			matrix[++j] = ft_strdup(shell->envp[i]);
			if (!matrix[j])
				return (0);
		}
	}
	return (matrix);
}

int	ft_unset(char **unset_mat, t_shell *shell)
{
	int		i;
	int		j;
	int		g;
	char	**env_copy;

	j = 0;
	if (matrix_len(unset_mat) < 2)
		return (1);
	else
	{
		while (unset_mat[++j])
		{
			g = 0;
			i = -1;
			env_copy = create_matrix(unset_mat[j], shell);
			collect_garbage(shell, 0, env_copy);
			if (env_copy)
				shell->envp = env_copy;
		}
	}
	return (0);
}
