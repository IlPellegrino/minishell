/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:41:07 by nromito           #+#    #+#             */
/*   Updated: 2024/06/04 12:15:42 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_env(char **env_mat, t_shell *shell)
{
	int	i;
	int	pos;

	i = -1;
	if (matrix_len(env_mat) < 2)
	{
		while (shell->envp[++i])
		{
			pos = -1;
			while (shell->envp[i][++pos])
			{
				if (shell->envp[i][pos] == '=')
				{
					printf("%s\n", shell->envp[i]);
					break ;
				}
			}
		}
		return (1);
	}
	else
		ft_error(shell, ENV, env_mat[1]);
	return (0);
}
