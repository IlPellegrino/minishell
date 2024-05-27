/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:40:46 by nromito           #+#    #+#             */
/*   Updated: 2024/05/25 12:52:37 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_addtoenv()
{
	
	
	return (0);
}

int	ft_getenv()
{
	return (0);
}

int	ft_export(char **export_mat, char **env)
{
	int	i;
	int	pos;

	i = -1;
	pos = -1;
	if (export_mat[0])
	{
		if (matrix_len(export_mat) < 2)
		{
			while (env[++i])
				printf("declare -x %s\n", env[i]);
			return (0);
		}
		else
		{
			i = 0;
			while (export_mat[++i])
			{
				while (export_mat[i][++pos] && export_mat[i][pos] != '=')
				{
					if (!ft_isalpha(export_mat[i][pos]) && export_mat[i][pos] != US)
					{
						printf("minishell: export: `%s': not a valid identifier", export_mat[i], stderr);
						return (1);
					}
					// ft_addtoenv(export_mat[i], env);
				}
				
			}
			return (0);
		}
	}
	return (1);
}
