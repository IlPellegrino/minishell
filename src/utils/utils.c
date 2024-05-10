/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:59:43 by nromito           #+#    #+#             */
/*   Updated: 2024/05/10 13:56:02 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_matrix(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		printf("%s\n", mat[i]);
		i++;
	}
}

int	ft_error(char *str, int error)
{
	if (str)
	{
		write (2, str, ft_strlen(str));
		write (2, "\n", 1);
	}
	return (error);
}