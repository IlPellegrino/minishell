/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:22:04 by nromito           #+#    #+#             */
/*   Updated: 2024/06/03 12:23:54 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrix_dup(char **matrix)
{
	int		i;
	int		size;
	char	**dup;

	size = 0;
	while (matrix[size])
		size++;
	dup = ft_calloc(sizeof(char *), size + 1);
	i = -1;
	while (matrix[++i])
		dup[i] = ft_strdup(matrix[i]);
	return (dup);
}
