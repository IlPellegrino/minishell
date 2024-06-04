/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:42:43 by ciusca            #+#    #+#             */
/*   Updated: 2024/06/04 14:19:22 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_space(char *index)
{
	int	i;

	i = 0;
	while (index[i] != SPACE)
		i++;
	if (!index[i])
		return (0);
	return (1);
}

void	free_matrix(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
	mat = NULL;
}
