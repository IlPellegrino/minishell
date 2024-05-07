/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:59:43 by nromito           #+#    #+#             */
/*   Updated: 2024/05/07 12:43:24 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	garbage_collector(t_shell *shell)
{
	t_garbage	*garbage;
	
	garbage = shell->collector;
	while (garbage)
	{
		if (garbage->flag == 0)
			free(garbage->arg);
		else if (garbage->flag == 1)
			free_matrix(garbage->arg);
		garbage = garbage->next;
	}
}

void	print_matrix(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		printf("%sEND\n", mat[i]);
		i++;
	}
}