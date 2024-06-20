/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:41:30 by nromito           #+#    #+#             */
/*   Updated: 2024/06/20 15:08:25 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_not_valid(char *to_delete, int len)
{
	int	valid;

	valid = 0;
	if (!ft_isalnum(to_delete[len]) && to_delete[len] != US)
		valid = 1;
	else if (to_delete[len] == '+' || to_delete[len] == '=')
		valid = 1;
	else if (ft_isdigit(to_delete[0]))
		valid = 1;
	return (valid);
}

int	calculate_len(char *to_delete, t_shell *shell)
{
	int	len;

	len = -1;
	if (!to_delete[0])
		return (ft_error(shell, UNSET, to_delete), 0);
	while (to_delete[++len])
		if (is_not_valid(to_delete, len))
			return (ft_error(shell, UNSET, to_delete), 0);
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
			return (collect_garbage(shell, 0, matrix), NULL);
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
