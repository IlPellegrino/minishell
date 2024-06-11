/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:41:30 by nromito           #+#    #+#             */
/*   Updated: 2024/06/11 15:00:09 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	calculate_len(char *to_delete, t_shell *shell)
{
	int	len;

	len = -1;
	while (to_delete[++len])
	{
		if ((!ft_isalpha(to_delete[len]) && to_delete[len] != US)
			&& ft_isdigit(to_delete[0]))
		{
			ft_error(shell, UNSET, to_delete);
			return (0);
		}
	}
	return (len);
}

char	*dup_env(char *to_check, char *to_delete, int len, int len2)
{
	char	*result;

	result = 0;
	if (len2 == len)
	{
		if (ft_strncmp(to_check, to_delete, len))
		{
			result = ft_strdup(to_check);
			if (!result)
				return (0);
		}
		
	}
	else
	{
		result = ft_strdup(to_check);
		if (!result)
			return (0);
	}
	printf("matrix BEFORE = %s\n", result);
	return (result);
}

char	**create_matrix(char *to_delete, t_shell *shell)
{
	int		i;
	int		j;
	int		len;
	int		len2;
	char	**matrix;

	i = -1;
	j = -1;
	matrix = ft_calloc(sizeof (char **), matrix_len(shell->envp) + 1);
	if (!matrix)
		return (0);
	while (shell->envp[++i])
	{
		len2 = -1;
		len = calculate_len(to_delete, shell);
		if (!len)
			return (0);
		while (shell->envp[i][++len2] && shell->envp[i][len2] != '=')
			;
		matrix[++j] = dup_env(shell->envp[i], to_delete, len, len2);
		if (matrix[j] == NULL && j <= matrix_len(shell->envp))
			j--;
	}
	return (matrix);
}

int	ft_unset(char **unset_mat, t_shell *shell)
{
	int		j;
	char	**env_copy;

	j = 0;
	if (matrix_len(unset_mat) < 2)
		return (1);
	else
	{
		while (unset_mat[++j])
		{
			env_copy = create_matrix(unset_mat[j], shell);
			if (env_copy)
			{
				shell->envp = ft_matrix_dup(env_copy);
				collect_garbage(shell, 0, shell->envp);
				free_matrix(env_copy);
			}
		}
		return (1);
	}
	return (0);
}
